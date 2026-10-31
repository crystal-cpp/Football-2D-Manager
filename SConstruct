#!/usr/bin/env python
import os
import sys

# 1. Load the SCons build options from the Godot bindings folder
opts = Variables()
opts.Add(EnumVariable("platform", "Target platform", sys.platform, allowed_values=("win32", "windows", "linux", "darwin")))
opts.Add(EnumVariable("target", "Compilation target", "template_debug", allowed_values=("template_debug", "template_release")))

env = Environment(variables=opts)

# 2. Add include directories for your source and godot headers
env.Append(CPPPATH=["src", "godot-cpp/include", "godot-cpp/gen/include"])

# 3. Import environment configurations to handle cross-dependencies
Export("env")
SConscript("godot-cpp/SConstruct")

# 4. Link against the static godot-cpp library you compiled earlier
if env["platform"] in ["win32", "windows"]:
    env.Append(LIBS=["godot-cpp.windows.template_debug.x86_64"])
    # Explicitly add the .dll extension to the target path string
    target_path = "demo/bin/libfootball.windows.template_debug.x86_64.dll"

# 5. Find all custom C++ source code files in your src folder
sources = Glob("src/*.cpp")

# 6. Build your custom logic into a shared library (.dll) inside demo/bin
env.SharedLibrary(target=target_path, source=sources)
