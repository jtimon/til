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
    WindowsX64,
    MacosX64,
    MacosArm64,
    TempleosX86,
    // Future: more targets
}

pub fn target_from_str(s: &str) -> Result<Target, String> {
    match s.to_lowercase().as_str() {
        "linux-x64" | "linux-x86_64" | "linux-amd64" => Ok(Target::LinuxX64),
        "linux-arm64" | "linux-aarch64" => Ok(Target::LinuxArm64),
        "windows-x64" | "windows-x86_64" | "win64" => Ok(Target::WindowsX64),
        "macos-x64" | "macos-x86_64" | "darwin-x64" => Ok(Target::MacosX64),
        "macos-arm64" | "macos-aarch64" | "darwin-arm64" => Ok(Target::MacosArm64),
        "templeos-x86" | "templeos" => Ok(Target::TempleosX86),
        _ => Err(format!(
            "Unknown target '{}'. Supported targets: linux-x64, linux-arm64, windows-x64, macos-x64, macos-arm64, templeos-x86",
            s
        )),
    }
}

pub fn target_to_str(target: &Target) -> &'static str {
    match target {
        Target::LinuxX64 => "linux-x64",
        Target::LinuxArm64 => "linux-arm64",
        Target::WindowsX64 => "windows-x64",
        Target::MacosX64 => "macos-x64",
        Target::MacosArm64 => "macos-arm64",
        Target::TempleosX86 => "templeos-x86",
    }
}

// ---------- Target/Lang compatibility

pub fn default_lang_for_target(target: &Target) -> Lang {
    match target {
        Target::TempleosX86 => Lang::HolyC,
        _ => Lang::C,
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

pub fn toolchain_command(target: &Target, lang: &Lang) -> Result<&'static str, String> {
    match (target, lang) {
        // Linux x64 - native gcc
        (Target::LinuxX64, Lang::C) => Ok("gcc"),
        // Linux ARM64 - cross-compiler
        (Target::LinuxArm64, Lang::C) => Ok("aarch64-linux-gnu-gcc"),
        // Windows x64 - MinGW cross-compiler
        (Target::WindowsX64, Lang::C) => Ok("x86_64-w64-mingw32-gcc"),
        // macOS - clang
        (Target::MacosX64, Lang::C) => Ok("clang"),
        (Target::MacosArm64, Lang::C) => Ok("clang"),
        // TempleOS - HolyC compiler (placeholder)
        (Target::TempleosX86, Lang::HolyC) => Ok("holyc"),
        // Invalid combinations
        _ => Err(format!(
            "No toolchain available for target '{}' with lang '{}'",
            target_to_str(target),
            lang_to_str(lang)
        )),
    }
}

pub fn toolchain_extra_args(target: &Target, _lang: &Lang) -> Vec<&'static str> {
    match target {
        // macOS ARM64 needs target specification
        Target::MacosArm64 => vec!["-target", "arm64-apple-macos11"],
        Target::MacosX64 => vec!["-target", "x86_64-apple-macos10.12"],
        // Windows needs to link against Windows libraries
        Target::WindowsX64 => vec![],
        _ => vec![],
    }
}

pub fn executable_extension(target: &Target) -> &'static str {
    match target {
        Target::WindowsX64 => ".exe",
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
