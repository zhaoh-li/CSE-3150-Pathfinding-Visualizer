#pragma once
#include "Types.h"

namespace pf {
struct RunStats {
    int    nodesExpanded = 0;
    Cost   pathCost = 0;          // sum of real edge weights, for every algorithm
    int    pathLength = 0;        // edges, not nodes
};
}
