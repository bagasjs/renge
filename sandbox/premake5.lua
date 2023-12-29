project "sandbox"
    kind "ConsoleApp"
    language "C"

    targetdir ("%{wks.location}/build/bin/" .. outputdir)
    objdir ("%{wks.location}/build/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/main.c",
        "../vendors/glad/src/glad.c",
    }

    includedirs {
        "../renge/src/",
        "../vendors/glad/include/",
    }

    links {
        "renge",
        "GL",
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
