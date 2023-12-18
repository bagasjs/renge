project "renge"
    kind "SharedLib"
    language "C"

    targetdir ("%{wks.location}/build/bin/" .. outputdir)
    objdir ("%{wks.location}/build/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/**.c",
        "%{prj.location}/src/**.h",
    }

    includedirs {
        "%{prj.location}/src",
    }

    filter "system:windows"
        staticruntime "On"
        defines {
            "RN_SHARED",
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

    filter "system:linux"
        defines {
            "RN_SHARED",
        }

        links {
            "X11",
        }

