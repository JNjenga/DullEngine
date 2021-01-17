workspace "DullEngine"
    location "Workspace"
    language "C++"
    architecture "x86_64"

    configurations {"Debug", "Release"}
    
	filter {"configurations:Debug"}
		symbols "On"
	filter {}
	
	filter {"configurations:Release"}
		optimize "On"
	filter {}

    targetdir("Build/%{cfg.longname}")
    objdir("Build/Obj/%{cfg.longname}")

    project "DEngine"
        kind "SharedLib"
        language "C++"

        files 
        {
            "Engine/src/**.h",
            "Engine/src/**.cpp"
        }

        defines { "GLFW_STATIC","GLEW_STATIC", "DE_EXPORTS_"} 
        
        libdirs
        {
            "Engine/3rdParty/glfw3/lib-vc2017",
            "Engine/3rdParty/glew/lib/x64",
        }

        includedirs
        {
            "Engine/3rdParty/glfw3/include",
            "Engine/3rdParty/glew/include",
            "Engine/3rdParty/glm",
        }

        links { "Opengl32", "glfw3", "glew32s" }

    project "SandBox"
        kind "ConsoleApp"
        language "C++"

        files 
        {
            "SandBox/src/**.h",
            "SandBox/src/**.cpp"
        }

        includedirs
        {
            "Engine/src",
            "Engine/3rdParty/glfw3/include",
            "Engine/3rdParty/glew/include",
            "Engine/3rdParty/glm",
        }

        links { "DEngine" }

