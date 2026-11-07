#pragma once
#include "Map.h"
#include <string>

namespace pf {

// Base class for every generator
class MapGenerator {                                       // W1
public:
    virtual ~MapGenerator() = default;
    virtual std::string name() const = 0;
    virtual Map generate(int w, int h, unsigned seed) = 0;   // same seed, same map; border is walls; w, h >= 3
};

class RandomWallGenerator : public MapGenerator {          // W1
public:
    std::string name() const override;
    Map generate(int w, int h, unsigned seed) override;
private:
    float wallChance_ = 0.25f;
};

}
