# Pathfinding Visualizer

A C++17 pathfinding visualizer: weighted grid maps, step-by-step search algorithms, problem modes (waypoints, tours, spanning trees) and routing on a real campus map.

**Team plan:** the planning files (`TODO.md`, `TODO_A.md` … `TODO_E.md`, `Interfaces.md`, `Conventions.md`) are shared with the team separately and are not part of this repo.

## Build

Needs CMake 3.20+ and a C++17 compiler. CMake downloads raylib, Dear ImGui, rlImGui and nlohmann/json on the first configure.

```
cmake -S . -B build
cmake --build build
./build/src/pathfinder
```

Tests only (no graphics, what CI runs):

```
cmake -S . -B build-tests -DPF_BUILD_GRAPHICS=OFF
cmake --build build-tests
ctest --test-dir build-tests --output-on-failure
```

_C writes the full README (build steps, Release vs Debug, credits and licenses) in week 4._
