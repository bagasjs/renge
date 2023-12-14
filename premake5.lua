workspace "Renge Engine"
    architecture "x86_64"
    configurations {
        "Debug",
        "Release",
        "Dist",
    }
    toolset "clang"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "renge"
include "sandbox"
