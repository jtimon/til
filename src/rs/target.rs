// Target and Lang definitions for cross-compilation support
// Mirrors src/self/target.til

// ---------- Lang enum - codegen backend languages

#[derive(Debug, Clone, PartialEq)]
pub enum Lang {
    C,
    HolyC,
    TIL,  // TIL-to-TIL (for debugging: shows desugared, dead-code-eliminated output)
    // Future: Mojo, WASM, etc.
}

pub fn lang_from_str(s: &str) -> Result<Lang, String> {
    match s.to_lowercase().as_str() {
        "c" => Ok(Lang::C),
        "holyc" => Ok(Lang::HolyC),
        "til" => Ok(Lang::TIL),
        _ => Err(format!("Unknown lang '{}'. Supported langs: c, holyc, til", s)),
    }
}

pub fn lang_to_str(lang: &Lang) -> &'static str {
    match lang {
        Lang::C => "c",
        Lang::HolyC => "holyc",
        Lang::TIL => "til",
    }
}

#[allow(dead_code)]
pub fn lang_file_extension(lang: &Lang) -> &'static str {
    match lang {
        Lang::C => "c",
        Lang::HolyC => "hc",
        Lang::TIL => "til",
    }
}

// ---------- Target enum - supported platforms

#[derive(Debug, Clone, PartialEq)]
pub enum Target {
    LinuxX64,
    LinuxArm64,
    LinuxRiscv64,
    WindowsX64,
    MacosX64,
    MacosArm64,
    Wasm32,
    TempleosX86,
}

pub fn target_from_str(s: &str) -> Result<Target, String> {
    match s.to_lowercase().as_str() {
        "linux-x64" | "linux-x86_64" | "linux-amd64" => Ok(Target::LinuxX64),
        "linux-arm64" | "linux-aarch64" => Ok(Target::LinuxArm64),
        "linux-riscv64" | "linux-riscv" | "riscv64" => Ok(Target::LinuxRiscv64),
        "windows-x64" | "windows-x86_64" | "win64" => Ok(Target::WindowsX64),
        "macos-x64" | "macos-x86_64" | "darwin-x64" => Ok(Target::MacosX64),
        "macos-arm64" | "macos-aarch64" | "darwin-arm64" => Ok(Target::MacosArm64),
        "wasm32" | "wasm" | "webassembly" => Ok(Target::Wasm32),
        "templeos-x86" | "templeos" => Ok(Target::TempleosX86),
        _ => Err(format!(
            "Unknown target '{}'. Supported targets: linux-x64, linux-arm64, linux-riscv64, windows-x64, macos-x64, macos-arm64, wasm32, templeos-x86",
            s
        )),
    }
}

pub fn target_to_str(target: &Target) -> &'static str {
    match target {
        Target::LinuxX64 => "linux-x64",
        Target::LinuxArm64 => "linux-arm64",
        Target::LinuxRiscv64 => "linux-riscv64",
        Target::WindowsX64 => "windows-x64",
        Target::MacosX64 => "macos-x64",
        Target::MacosArm64 => "macos-arm64",
        Target::Wasm32 => "wasm32",
        Target::TempleosX86 => "templeos-x86",
    }
}

// ---------- Target/Lang compatibility

pub fn default_lang_for_target(target: &Target) -> Lang {
    match target {
        Target::TempleosX86 => Lang::HolyC,
        Target::LinuxX64 | Target::LinuxArm64 | Target::LinuxRiscv64 |
        Target::WindowsX64 | Target::MacosX64 | Target::MacosArm64 | Target::Wasm32 => Lang::C,
    }
}

pub fn supported_langs_for_target(target: &Target) -> Vec<Lang> {
    match target {
        Target::TempleosX86 => vec![Lang::HolyC, Lang::TIL],
        _ => vec![Lang::C, Lang::TIL],  // TIL is always supported (for debugging)
    }
}

pub fn is_lang_supported_for_target(lang: &Lang, target: &Target) -> bool {
    supported_langs_for_target(target).contains(lang)
}

pub fn validate_lang_for_target(lang: &Lang, target: &Target) -> Result<(), String> {
    if is_lang_supported_for_target(lang, target) {
        Ok(())
    } else {
        let supported: Vec<&str> = supported_langs_for_target(target)
            .iter()
            .map(|l| lang_to_str(l))
            .collect();
        Err(format!(
            "Lang '{}' is not supported for target '{}'. Supported langs for this target: {}",
            lang_to_str(lang),
            target_to_str(target),
            supported.join(", ")
        ))
    }
}

// ---------- Toolchain commands

// Issue #131: Check if a compiler command is clang (for warning flag selection)
pub fn is_clang(cmd: &str) -> bool {
    cmd.contains("clang")
}

pub fn toolchain_command(target: &Target, lang: &Lang) -> Result<String, String> {
    match (target, lang) {
        // Linux: gcc by default (use --cc=clang to override)
        (Target::LinuxX64, Lang::C) => Ok("gcc".to_string()),
        (Target::LinuxArm64, Lang::C) => Ok("aarch64-linux-gnu-gcc".to_string()),
        (Target::LinuxRiscv64, Lang::C) => Ok("riscv64-linux-gnu-gcc".to_string()),
        // Windows: mingw-gcc by default (use --cc=clang to override)
        (Target::WindowsX64, Lang::C) => Ok("x86_64-w64-mingw32-gcc".to_string()),
        // macOS: clang only (Apple's default, gcc is symlink to clang)
        (Target::MacosX64, Lang::C) => Ok("clang".to_string()),
        (Target::MacosArm64, Lang::C) => Ok("clang".to_string()),
        (Target::Wasm32, Lang::C) => Ok("clang".to_string()),
        (Target::TempleosX86, Lang::HolyC) => Ok("holyc".to_string()),
        // Invalid combinations
        _ => Err(format!(
            "No toolchain available for target '{}' with lang '{}'",
            target_to_str(target),
            lang_to_str(lang)
        )),
    }
}

pub fn toolchain_extra_args(target: &Target, _lang: &Lang, compiler: &str) -> Vec<&'static str> {
    // Bug #99: -Wall -Wextra -Werror with suppressions for unfixed warnings.
    // Remove suppressions as warnings get fixed.
    // Note: Some flags are compiler-specific (gcc vs clang)
    let common: &[&str] = &[
        "-Wall", "-Wextra", "-Werror",
        // Suppressions for unfixed warnings (Bug #99):
        "-Wno-unused-variable",           // 1514 occurrences
        "-Wno-unused-but-set-variable",   // 386 occurrences
        "-Wno-unused-label",              // 153 occurrences
    ];
    let gcc_only: &[&str] = &[
        "-Wno-dangling-pointer",          // 971 occurrences (high priority to fix) - GCC only
    ];
    let clang_only: &[&str] = &[
        "-Wno-sometimes-uninitialized",   // clang-specific warning about exception control flow
        "-Wno-self-assign",               // til_result = til_result patterns in generated code
        "-Wno-c23-extensions",            // unnamed parameters in function definitions
        "-Wno-uninitialized",             // variable used before initialization in some paths
    ];
    // Issue #131: Use compiler command to determine which flags to use
    let use_clang = is_clang(compiler);
    match target {
        // macOS and wasm always use clang target flags
        Target::MacosArm64 => [&["-target", "arm64-apple-macos11"], common, clang_only].concat(),
        Target::MacosX64 => [&["-target", "x86_64-apple-macos10.12"], common, clang_only].concat(),
        Target::Wasm32 => [&["--target=wasm32", "-nostdlib", "-Wl,--no-entry", "-Wl,--export-all"], common, clang_only].concat(),
        Target::TempleosX86 => todo!("HolyC doesn't support these flags"),
        // Linux and Windows: use compiler-specific flags based on --cc flag
        _ => if use_clang {
            [common, clang_only].concat()
        } else {
            [common, gcc_only].concat()
        },
    }
}

pub fn executable_extension(target: &Target) -> &'static str {
    match target {
        Target::WindowsX64 => ".exe",
        Target::Wasm32 => ".wasm",
        _ => "",
    }
}

// ---------- Detect current platform

pub fn detect_current_target() -> Target {
    #[cfg(all(target_os = "linux", target_arch = "x86_64"))]
    return Target::LinuxX64;

    #[cfg(all(target_os = "linux", target_arch = "aarch64"))]
    return Target::LinuxArm64;

    #[cfg(all(target_os = "windows", target_arch = "x86_64"))]
    return Target::WindowsX64;

    #[cfg(all(target_os = "macos", target_arch = "x86_64"))]
    return Target::MacosX64;

    #[cfg(all(target_os = "macos", target_arch = "aarch64"))]
    return Target::MacosArm64;

    // Default fallback
    #[cfg(not(any(
        all(target_os = "linux", target_arch = "x86_64"),
        all(target_os = "linux", target_arch = "aarch64"),
        all(target_os = "windows", target_arch = "x86_64"),
        all(target_os = "macos", target_arch = "x86_64"),
        all(target_os = "macos", target_arch = "aarch64"),
    )))]
    return Target::LinuxX64;
}
