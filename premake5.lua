build_configurations = {}

build_configurations[0] = "Debug"
build_configurations[1] = "RelWithDebInfo"
build_configurations[2] = "Release"


function get_conan_config()

  local configurations = {}

  for i,build_cfg in ipairs(build_configurations) do

    include("../../build/deps/"..build_cfg.."/conanbuildinfo.premake.lua")

    configurations[build_cfg] = {}

    local cfg = configurations[build_cfg]

    cfg["includedirs"] = conan_includedirs
    cfg["libdirs"] = conan_libdirs
    cfg["bindirs"] = conan_bindirs
    cfg["libs"] = conan_libs
    cfg["system_libs"] = conan_system_libs
    cfg["defines"] = conan_defines
    cfg["frameworks"] = conan_frameworks

  end

  return configurations

end

function setup_dependencies(conan_config)

  for i,build_cfg in ipairs(build_configurations) do

    local cfg = conan_config[build_cfg]
    filter("configurations:"..build_cfg)

      includedirs{cfg["includedirs"]}
      libdirs{cfg["libdirs"]}
      links{cfg["libs"]}
      links{cfg["system_libs"]}
      links{cfg["frameworks"]}
      defines{cfg["defines"]}
      bindirs{cfg["bindirs"]}

  end

end

workspace "WindowTest"
   configurations { "Debug", "RelWithDebInfo", "Release" }
   location "build"
   conan_cfg = get_conan_config()
   setup_dependencies(conan_cfg)
   


project "WindowTest"
   kind "ConsoleApp"
   language "C++"
   language "C"
   targetdir "bin/%{cfg.buildcfg}"
   location "build"

   files { "premake5.lua", "include/**.h", "src/**.h", "src/**.c",
           "src/**.cpp", "src/build/**.txt" }


   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter { "configurations:RelWithDebInfo" }
      defines { "NDEBUG" }
      symbols "On"
      optimize "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
