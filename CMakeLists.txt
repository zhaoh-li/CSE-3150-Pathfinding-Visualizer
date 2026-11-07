cmake_minimum_required(VERSION 3.20)
project(Pathfinder LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# CI turns this OFF, so the automatic build needs no raylib or ImGui.
option(PF_BUILD_GRAPHICS "Build the app (raylib + ImGui)" ON)

include(cmake/Dependencies.cmake)   # raylib, ImGui, rlImGui, nlohmann/json (pinned versions)
include(cmake/PfHelpers.cmake)      # pf_library() and pf_test()

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
