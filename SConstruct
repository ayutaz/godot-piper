#!/usr/bin/env python
import os
import sys

# Add godot-cpp to path
sys.path.append("godot-cpp/")

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

# Platform-specific settings
if env["platform"] == "windows":
    env.Append(CPPDEFINES=["WIN32", "_WIN32", "_WINDOWS", "_CRT_SECURE_NO_WARNINGS"])
    env.Append(CCFLAGS=["/MD", "/EHsc"])
    if env["target"] in ["editor", "template_debug"]:
        env.Append(CPPDEFINES=["DEBUG", "_DEBUG"])
    else:
        env.Append(CPPDEFINES=["NDEBUG"])

elif env["platform"] == "linux":
    env.Append(CCFLAGS=["-fPIC", "-Wwrite-strings"])
    env.Append(LINKFLAGS=["-Wl,-R,'$$ORIGIN'"])
    if env["target"] in ["editor", "template_debug"]:
        env.Append(CCFLAGS=["-g", "-O0"])
    else:
        env.Append(CCFLAGS=["-O3"])

elif env["platform"] == "macos":
    env.Append(CCFLAGS=["-std=c++17"])
    if env["target"] in ["editor", "template_debug"]:
        env.Append(CCFLAGS=["-g", "-O0"])
    else:
        env.Append(CCFLAGS=["-O3"])
    # Support both Intel and Apple Silicon
    if env["arch"] == "universal":
        env.Append(CCFLAGS=["-arch", "x86_64", "-arch", "arm64"])
        env.Append(LINKFLAGS=["-arch", "x86_64", "-arch", "arm64"])
    elif env["arch"] == "x86_64":
        env.Append(CCFLAGS=["-arch", "x86_64"])
        env.Append(LINKFLAGS=["-arch", "x86_64"])
    elif env["arch"] == "arm64":
        env.Append(CCFLAGS=["-arch", "arm64"])
        env.Append(LINKFLAGS=["-arch", "arm64"])

elif env["platform"] == "android":
    # Android-specific settings
    env.Append(CPPDEFINES=["ANDROID"])
    env.Append(CCFLAGS=["-fPIC"])

# Determine the library name and output path
if env["platform"] == "macos":
    library_name = "libgodot_piper.{}.{}.framework/libgodot_piper.{}.{}".format(
        env["platform"], env["target"], env["platform"], env["target"]
    )
else:
    library_name = "libgodot_piper{}{}".format(env["suffix"], env["SHLIBSUFFIX"])

# Set the output directory
bin_path = "addons/godot_piper/bin/"
library_path = bin_path + library_name

# Create the library
if env["platform"] == "macos":
    plat_bin_path = bin_path + "libgodot_piper.{}.{}.framework/".format(env["platform"], env["target"])
    library = env.SharedLibrary(
        plat_bin_path + "libgodot_piper.{}.{}".format(env["platform"], env["target"]),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        library_path,
        source=sources,
    )

Default(library)