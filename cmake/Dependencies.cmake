# Third-party libraries, downloaded by CMake at configure time.
# Every library is pinned to a fixed version, so all machines build the same code.
# Owner: C. Ask the group before adding a library (see Conventions.md in the team plan).

include(FetchContent)

# nlohmann/json (E's geo code). Header-only.
FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(nlohmann_json)

if(PF_BUILD_GRAPHICS)
    # raylib
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(raylib)

    # Dear ImGui (no CMake of its own: we only download it)
    FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.91.5
        GIT_SHALLOW TRUE
    )
    FetchContent_GetProperties(imgui)
    if(NOT imgui_POPULATED)
        FetchContent_Populate(imgui)
    endif()

    # rlImGui (connects ImGui to raylib; no CMake of its own either)
    # TODO(C): replace "main" with a fixed commit hash once the build works on every machine.
    FetchContent_Declare(
        rlimgui
        GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
        GIT_TAG main
    )
    FetchContent_GetProperties(rlimgui)
    if(NOT rlimgui_POPULATED)
        FetchContent_Populate(rlimgui)
    endif()

    # One library holding ImGui + rlImGui, linked by src/render only.
    add_library(pf_imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${rlimgui_SOURCE_DIR}/rlImGui.cpp
    )
    target_include_directories(pf_imgui SYSTEM PUBLIC ${imgui_SOURCE_DIR} ${rlimgui_SOURCE_DIR})
    target_link_libraries(pf_imgui PUBLIC raylib)
endif()
