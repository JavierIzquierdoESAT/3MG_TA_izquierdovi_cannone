workspace "MyWorkspace"
   configurations { "Debug", "Release" }

project "EngineWindow"
   kind "ConsoleApp"
   language "C++"
   files { "premake5.lua", "include/*.h", "src/*.h", "src/*.cpp" }

   filter { "configurations:Debug" }
      defines { "DEBUG" }
      symbols "On"

    filter { "configurations:RelWithSym" }
      defines { "NDEBUG" }
      symbols "On"
      optimize "On"

   filter { "configurations:Release" }
      defines { "NDEBUG" }
      optimize "On"
