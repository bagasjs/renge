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
