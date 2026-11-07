#pragma once
#include "Algorithm.h"

namespace pf {
// Runs a search to the end, without animation. Used by B, D and E.
inline Path findPath(Pathfinder& pf, const Graph& g, NodeId start, NodeId goal) {
    pf.start(g, start, goal);
    while (pf.step()) {}
    return pf.path();
}
}
