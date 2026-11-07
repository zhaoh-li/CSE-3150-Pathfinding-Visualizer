#pragma once
#include "Terrain.h"
#include "core/Graph.h"
#include <vector>

namespace pf {

// What generators return. Cells are private, so the W3 switch to Grid breaks nobody.
class Map {                                       // W1
public:
    Map(int width = 0, int height = 0, Terrain fill = Terrain::Grass);
    int     width() const;
    int     height() const;
    Terrain at(int x, int y) const;               // asserts outside the map
    void    set(int x, int y, Terrain t);         // ignores cells outside the map
    GridGraph toGraph() const;                    // 4 directions; no edges into or out of walls
private:
    int width_ = 0, height_ = 0;
    std::vector<Terrain> cells_;
};

}
