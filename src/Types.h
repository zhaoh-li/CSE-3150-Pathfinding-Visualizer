#pragma once
#include <vector>

namespace pf {
using NodeId = int;                   // 0 .. nodeCount() - 1
using Cost   = float;                 // grass = 1
using Path   = std::vector<NodeId>;   // start first, goal last; empty = no route
}
