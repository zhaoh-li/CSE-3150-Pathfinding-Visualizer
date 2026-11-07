#pragma once
#include "Types.h"

namespace pf {
enum class Terrain { Grass, Mud, Water, Wall };

constexpr Cost cost(Terrain t) {
    switch (t) {
        case Terrain::Grass: return 1;
        case Terrain::Mud:   return 3;
        case Terrain::Water: return 5;
        default:             return 0;   // Wall: never gets edges, so never used
    }
}
}
