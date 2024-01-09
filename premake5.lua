
conan = {}
configs = {'Debug','Release','RelWithDebInfo'}

for i = 1,3 do

        include("../../build/deps/"..configs[i].."/conanbuildinfo.premake.lua")
        conan[configs[i]] = {}
        local cfg = conan[configs[i]]
        cfg["build_type"] = conan_build_type
        cfg["arch"] = conan_arch
        cfg["includedirs"] = conan_includedirs
        cfg["libdirs"] = conan_libdirs
        cfg["bindirs"] = conan_bindirs
        cfg["libs"] = conan_libs
        cfg["system_libs"] = conan_system_libs
        cfg["defines"] = conan_defines
        cfg["cxxflags"] = conan_cxxflags
        cfg["cflags"] = conan_cflags
        cfg["sharedlinkflags"] = conan_sharedlinkflags
        cfg["exelinkflags"] = conan_exelinkflags
        cfg["frameworks"] = conan_frameworks

end

function conan_config_exec()

    configs = {'Debug','Release','RelWithDebInfo'}
    for i = 1,3 do

            local cfg = conan[configs[i]]
            filter("configurations:"..configs[i])

                linkoptions { cfg["exelinkflags"] }
                includedirs{ cfg["includedirs"] }
                libdirs{ cfg["libdirs"] }
                links{ cfg["libs"] }
                links{ cfg["system_libs"] }
                links{ cfg["frameworks"] }
                defines{ cfg["defines"] }

            filter{}

    end

end

function conan_config_lib()

    configs = {'Debug','Release','RelWithDebInfo'}
    for i = 1,3 do

        local cfg = conan[configs[i]]
        filter("configurations:"..configs[i])

            linkoptions { cfg["sharedlinkflags"] }
            includedirs{ cfg["includedirs"] }
            defines{ cfg["defines"] }

        filter{}

    end

end


workspace "CopperfieldEngine"
   configurations { "Debug",  "Release", "RelWithDebInfo" }
   architecture "x64"
   cppdialect "c++20"
   location "build"
   startproject "DemoObj"

   filter "configurations:Debug"
           defines { "DEBUG" }
          symbols "On"
          runtime "Debug"

   filter "configurations:Release"
           defines { "NDEBUG" }
           optimize "On"
           runtime "Release"

   filter "configurations:RelWithDebInfo"
           defines { "NDEBUG" }
           optimize "On"
           runtime "Release"
           symbols "On"

    filter {}


project "LibMath"

    kind "StaticLib"
    targetdir "build/%{cfg.buildcfg}"
    includedirs "include"
    conan_config_lib()
    warnings "High"

    files {
            "include/math/*.h",
            "src/math/*.cc"
    }

project "Imgui"

    kind "StaticLib"
    targetdir "build/%{cfg.buildcfg}"
    includedirs "include"
    conan_config_lib()
    warnings "High"

    files {
            "include/imgui/*.h",
            "src/imgui/*.cpp"
    }

project "LibSound"

    kind "StaticLib"
    targetdir "build/%{cfg.buildcfg}"
    includedirs "include"
    conan_config_lib()
    warnings "High"

    files {
            "include/sound/*.h",
            "src/sound/*.cpp"
    }

project "LibEngine"

    kind "StaticLib"
    targetdir "build/%{cfg.buildcfg}"
    includedirs "include"
    links "Imgui"
    links "LibMath"
    links "LibSound"
    conan_config_lib()
    pchheader "stdafx.hpp"
    pchsource "src/stdafx.cpp"
    forceincludes { "stdafx.hpp" }
    warnings "High"

    files {
            "premake5.lua",
            "src/build/conanfile.txt",
            "src/stdafx.cpp", "src/stdafx.hpp",
            "include/**.hpp",
            "src/**.cpp"
    }

project"DemoWindow"

    kind "ConsoleApp"
    language "C++"
    targetdir "build/%{prj.name}/%{cfg.buildcfg}"
    includedirs "include"
    links "LibEngine"
    warnings "High"

    conan_config_exec("Debug")
    conan_config_exec("Release")
    conan_config_exec("RelWithDebInfo")
    debugargs { _MAIN_SCRIPT_DIR .. "/examples/data" }

    files "examples/demo_window.cpp"

project"DemoDraw"

    kind "ConsoleApp"
    language "C++"
    targetdir "build/%{prj.name}/%{cfg.buildcfg}"
    includedirs "include"
    links "LibEngine"
    warnings "High"

    conan_config_exec("Debug")
    conan_config_exec("Release")
    conan_config_exec("RelWithDebInfo")
    debugargs { _MAIN_SCRIPT_DIR .. "/examples/data" }

    files "examples/demo_draw.cpp"

project"DemoInput"

    kind "ConsoleApp"
    language "C++"
    targetdir "build/%{prj.name}/%{cfg.buildcfg}"
    includedirs "include"
    links "LibEngine"
    warnings "High"

    conan_config_exec("Debug")
    conan_config_exec("Release")
    conan_config_exec("RelWithDebInfo")
    debugargs { _MAIN_SCRIPT_DIR .. "/examples/data" }

    files "examples/demo_input.cpp"

project"DemoECS"

    kind "ConsoleApp"
    language "C++"
    targetdir "build/%{prj.name}/%{cfg.buildcfg}"
    includedirs "include"
    links "LibEngine"
    warnings "High"

    conan_config_exec("Debug")
    conan_config_exec("Release")
    conan_config_exec("RelWithDebInfo")
    debugargs { _MAIN_SCRIPT_DIR .. "/examples/data" }

    files "examples/demo_ecs.cpp"

project"DemoObj"

    kind "ConsoleApp"
    language "C++"
    targetdir "build/%{prj.name}/%{cfg.buildcfg}"
    includedirs "include"
    links "LibEngine"
    warnings "High"

    conan_config_exec("Debug")
    conan_config_exec("Release")
    conan_config_exec("RelWithDebInfo")
    debugargs { _MAIN_SCRIPT_DIR .. "/examples/data" }

    files "examples/demo_obj.cpp"






project"TutorialBasics"

    kind "ConsoleApp"
    language "C++"
    targetdir "build/%{prj.name}/%{cfg.buildcfg}"
    includedirs "include"
    links "LibEngine"
    warnings "High"

    conan_config_exec("Debug")
    conan_config_exec("Release")
    conan_config_exec("RelWithDebInfo")
    debugargs { _MAIN_SCRIPT_DIR .. "/examples/data" }

    files "examples/window.cpp"

project"TestMultyThread"

      kind "ConsoleApp"
      language "C++"
      targetdir "build/%{prj.name}/%{cfg.buildcfg}"
      includedirs "include"
      links "LibEngine"
      warnings "High"

      conan_config_exec("Debug")
      conan_config_exec("Release")
      conan_config_exec("RelWithDebInfo")
      debugargs { _MAIN_SCRIPT_DIR .. "/examples/data" }

      files "examples/multythread_test.cpp"

project"TestECS"

    kind "ConsoleApp"
    language "C++"
    targetdir "build/%{prj.name}/%{cfg.buildcfg}"
    includedirs "include"
    links "LibEngine"
    warnings "High"

    conan_config_exec("Debug")
    conan_config_exec("Release")
    conan_config_exec("RelWithDebInfo")
    debugargs { _MAIN_SCRIPT_DIR .. "/examples/data" }

    files "examples/ecs.cpp"

project"TestOBJ"

    kind "ConsoleApp"
    language "C++"
    targetdir "build/%{prj.name}/%{cfg.buildcfg}"
    includedirs "include"
    links "LibEngine"

    conan_config_exec("Debug")
    conan_config_exec("Release")
    conan_config_exec("RelWithDebInfo")
    debugargs { _MAIN_SCRIPT_DIR .. "/examples/data" }

    files "examples/obj_example.cpp"

project"TestSound"

    kind "ConsoleApp"
    language "C++"
    targetdir "build/%{prj.name}/%{cfg.buildcfg}"
    includedirs "include"
    links "LibEngine"

    conan_config_exec("Debug")
    conan_config_exec("Release")
    conan_config_exec("RelWithDebInfo")
    debugargs { _MAIN_SCRIPT_DIR .. "/examples/data" }

    files "examples/sound_example.cpp"
