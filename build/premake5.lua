workspace "program_selector"
   configurations { "Debug", "Release" }

local function chapter_project(project_name)
   project(project_name)
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   targetdir "../bin/%{cfg.buildcfg}"

   files {
      "../src/" .. project_name .. "/*.h",
      "../src/" .. project_name .. "/*.hpp",
      "../src/" .. project_name .. "/*.c",
      "../src/" .. project_name .. "/*.cpp",
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
end

project "program_selector"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   targetdir "../bin/%{cfg.buildcfg}"

   files {
      "../src/*.h",
      "../src/*.hpp",
      "../src/*.c",
      "../src/*.cpp",
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

local handle = io.popen("ls -d ../src/*/ -1")
local folders = handle:read("*a")
handle:close()

for line in string.gmatch(folders,'[^\r\n]+') do
   local project_name = line:match(".*/(.*)/$")
   chapter_project(project_name)
end
