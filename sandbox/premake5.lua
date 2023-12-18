project "sandbox"
    kind "ConsoleApp"
    language "C"

    targetdir ("%{wks.location}/build/bin/" .. outputdir)
    objdir ("%{wks.location}/build/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/main.c",
    }

    includedirs {
        "../renge/src/",
    }

    links {
        "renge",
    }

    filter "configurations:Debug"
        defines "RN_DEBUG"
        symbols "On"
        debugger "GDB"

    filter "configurations:Release"
        defines "RN_RELEASE"
        symbols "On"

    filter "configurations:Dist"
        defines "RN_DIST"
        symbols "On"
