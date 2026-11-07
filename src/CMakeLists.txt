# One library per folder; each owner edits only their own folder's CMakeLists.txt.
add_subdirectory(core)       # A
add_subdirectory(problems)   # B
add_subdirectory(gen)        # D
add_subdirectory(editor)     # D
add_subdirectory(geo)        # E
add_subdirectory(io)         # E

if(PF_BUILD_GRAPHICS)
    add_subdirectory(render) # C (plus D's EditorPanel)

    # The app. At setup, main.cpp is only a placeholder window that proves the build works.
    add_executable(pathfinder main.cpp)
    target_link_libraries(pathfinder PRIVATE pf_render)
    pf_warnings(pathfinder)
endif()
