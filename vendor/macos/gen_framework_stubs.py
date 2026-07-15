#!/usr/bin/env python3
# Generate minimal tapi-tbd v4 framework link stubs from a Mach-O's
# undefined symbols (issue #25 phase 3, mac gui cross). `nm -m <macho>`
# annotates each undefined external symbol with the dylib/framework it
# comes from ("(from OpenGL)"); we group by that and emit one .tbd
# document per framework listing only the symbols actually referenced.
# The real Cocoa/OpenGL/... dylibs live on every mac and bind at runtime
# (same idea as the vendored libSystem.tbd), so these text stubs let a
# LINUX host cross-link a mac gui binary with no SDK.
#
# install-name per framework: on a mac we read the real value from the
# SDK's own framework .tbd (exact); off a mac (e.g. parse-testing this
# generator on linux) we fall back to a best-effort map and mark it.
import subprocess, sys, os, glob, re

# frameworks whose symbols we do NOT emit stubs for: libSystem is already
# vendored (vendor/macos/libSystem.tbd covers it + its reexports).
SKIP = {"libSystem"}

# Fallback install-names (used only when no SDK is present, e.g. linux
# parse-test). The Versions letter matters for the runtime LC_LOAD_DYLIB,
# so on a real mac we override these from the SDK .tbd.
FALLBACK_INSTALL = {
    "OpenGL":         "/System/Library/Frameworks/OpenGL.framework/Versions/A/OpenGL",
    "Cocoa":          "/System/Library/Frameworks/Cocoa.framework/Versions/A/Cocoa",
    "AppKit":         "/System/Library/Frameworks/AppKit.framework/Versions/C/AppKit",
    "Foundation":     "/System/Library/Frameworks/Foundation.framework/Versions/C/Foundation",
    "CoreFoundation": "/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation",
    "CoreGraphics":   "/System/Library/Frameworks/CoreGraphics.framework/Versions/A/CoreGraphics",
    "CoreVideo":      "/System/Library/Frameworks/CoreVideo.framework/Versions/A/CoreVideo",
    "CoreAudio":      "/System/Library/Frameworks/CoreAudio.framework/Versions/A/CoreAudio",
    "AudioToolbox":   "/System/Library/Frameworks/AudioToolbox.framework/Versions/A/AudioToolbox",
    "IOKit":          "/System/Library/Frameworks/IOKit.framework/Versions/A/IOKit",
    "CoreServices":   "/System/Library/Frameworks/CoreServices.framework/Versions/A/CoreServices",
    "ApplicationServices": "/System/Library/Frameworks/ApplicationServices.framework/Versions/A/ApplicationServices",
    "libobjc":        "/usr/lib/libobjc.A.dylib",
    "libc++":         "/usr/lib/libc++.1.dylib",
}

def sdk_install_name(fw):
    """On a mac, read the framework's real install-name from its SDK .tbd."""
    sdk = os.environ.get("SDKROOT")
    if not sdk:
        try:
            sdk = subprocess.check_output(["xcrun", "--show-sdk-path"], text=True).strip()
        except Exception:
            return None
    if fw.startswith("lib"):
        cands = glob.glob(f"{sdk}/usr/lib/{fw}*.tbd")
    else:
        cands = glob.glob(f"{sdk}/System/Library/Frameworks/{fw}.framework/**/{fw}.tbd", recursive=True) \
              + glob.glob(f"{sdk}/System/Library/Frameworks/{fw}.framework/{fw}.tbd")
    for c in cands:
        try:
            for line in open(c):
                m = re.match(r"\s*install-name:\s*'?\"?([^'\"]+)", line)
                if m:
                    return m.group(1).strip()
        except Exception:
            pass
    return None

def parse_nm(text):
    """Return {framework: sorted[symbols]} from `nm -m` undefined externals.
    `text` is the output of `nm -m <macho>` (Apple nm) or `llvm-nm -m`."""
    by_fw = {}
    for line in text.splitlines():
        # ... (undefined) external _sym (from Framework)
        m = re.search(r"\(undefined\)\s+external\s+(\S+)\s+\(from\s+([^)]+)\)", line)
        if not m:
            continue
        sym, fw = m.group(1), m.group(2).strip()
        if fw in SKIP:
            continue
        by_fw.setdefault(fw, set()).add(sym)
    return {fw: sorted(s) for fw, s in by_fw.items()}

def emit_one(fw, symbols, install):
    syms = ", ".join(symbols)
    return (
        "--- !tapi-tbd\n"
        "tbd-version:     4\n"
        "targets:         [ x86_64-macos, arm64-macos ]\n"
        f"install-name:    '{install}'\n"
        "exports:\n"
        "  - targets:         [ x86_64-macos, arm64-macos ]\n"
        f"    symbols:         [ {syms} ]\n"
        "...\n"
    )

if __name__ == "__main__":
    # Reads `nm -m <macho>` output on stdin, writes one <Framework>.tbd
    # stub per framework into <outdir> (default: current dir). Each is a
    # standalone tapi-tbd -- lld resolves symbols only from the FIRST doc
    # of a multi-doc file (treating the rest as reexports), so independent
    # frameworks MUST be separate files, each passed as its own linker
    # input. Caller picks nm: Apple `nm -m` on a mac, `llvm-nm -m`
    # elsewhere. e.g. on mac:  nm -m libraylib.a | gen_framework_stubs.py vendor/macos/frameworks
    outdir = sys.argv[1] if len(sys.argv) > 1 else "."
    os.makedirs(outdir, exist_ok=True)
    by_fw = parse_nm(sys.stdin.read())
    sys.stderr.write("frameworks: " + ", ".join(f"{k}={len(v)}" for k, v in sorted(by_fw.items())) + "\n")
    for fw in sorted(by_fw):
        install = sdk_install_name(fw) or FALLBACK_INSTALL.get(fw)
        if not install:
            sys.stderr.write(f"WARN: no install-name for framework {fw}; skipping\n")
            continue
        # framework name may contain no path chars; use it as the filename
        path = os.path.join(outdir, f"{fw}.tbd")
        with open(path, "w") as f:
            f.write(emit_one(fw, by_fw[fw], install))
        print(path)
