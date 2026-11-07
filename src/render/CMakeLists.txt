# Owner: C, except EditorPanel.cpp, whose line D adds (D owns that one line).
# Add each new .cpp to SOURCES in the week your TODO file schedules it,
# e.g. SOURCES App.cpp Renderer.cpp UI.cpp
# This is the only folder that links raylib and ImGui (through pf_imgui).
pf_library(pf_render
    SOURCES
    DEPS pf_core pf_problems pf_gen pf_editor pf_geo pf_io pf_imgui
)
