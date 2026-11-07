// Placeholder (owner: C). It only opens a window with an ImGui panel, to prove that
// CMake, raylib and rlImGui build on every machine. In week 1, C replaces it with:
//
//     #include "render/App.h"
//     int main() { pf::App app; app.run(); }
//
// raylib / ImGui are allowed here only until then; afterwards they live in src/render/.
#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"

int main() {
    InitWindow(1280, 720, "Pathfinding Visualizer");
    SetTargetFPS(60);
    rlImGuiSetup(true);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        rlImGuiBegin();
        ImGui::Begin("Setup check");
        ImGui::Text("The build works. Close this window to finish.");
        ImGui::End();
        rlImGuiEnd();
        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();
    return 0;
}
