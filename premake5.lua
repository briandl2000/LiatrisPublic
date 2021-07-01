workspace "Liatris"
    architecture "x64"
    startproject "Liatris Editor"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
    

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] =  "Liatris/vendor/GLFW/include"
IncludeDir["Glad"] =  "Liatris/vendor/Glad/include"
IncludeDir["ImGui"] = "Liatris/vendor/imgui"
IncludeDir["glm"] =   "Liatris/vendor/glm"
IncludeDir["entt"] =  "Liatris/vendor/entt/include"
IncludeDir["ImGuizmo"] =  "Liatris/vendor/ImGuizmo"
IncludeDir["tinygltf"] =  "Liatris/vendor/tinygltf"


group "Dependencies"
    include "Liatris/vendor/GLFW"
    include "Liatris/vendor/Glad"
    include "Liatris/vendor/imgui"

group ""

project "Liatris"
    location "Liatris"
    kind "StaticLib"
    cppdialect "C++17"
    language "C++"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "liapch.h"
    pchsource "Liatris/src/liapch.cpp"

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",

        "%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
        "%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.ImGuizmo}",
        "%{IncludeDir.tinygltf}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "files:Liatris/vendor/ImGuizmo/**.cpp"
    flags { "NoPCH" }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "LIA_PLATFORM_WINDOWS",
            "LIA_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "LIA_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "LIA_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "LIA_DIST"
        runtime "Release"
        optimize "on"

project "Liatris Editor"
    location "Liatris Editor"
    kind "ConsoleApp"
    cppdialect "C++17"
    language "C++"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs 
    {
        "Liatris/vendor/spdlog/include",
        "Liatris/src",
        "Liatris/vendor",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.ImGuizmo}",
        "%{IncludeDir.tinygltf}"
    }

    links
    {
        "Liatris"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "LIA_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "LIA_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "LIA_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "LIA_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    cppdialect "C++17"
    language "C++"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs 
    {
        "Liatris/vendor/spdlog/include",
        "Liatris/src",
        "Liatris/vendor",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}"
    }

    links
    {
        "Liatris"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "LIA_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "LIA_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "LIA_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "LIA_DIST"
        runtime "Release"
        optimize "on"