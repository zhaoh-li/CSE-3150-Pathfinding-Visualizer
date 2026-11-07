#pragma once
#include "core/Algorithm.h"
#include <memory>
#include <string>
#include <vector>

namespace pf {

// What every mode returns; C draws it. Plain data, no graphics.
struct ProblemResult {
    std::vector<Path> legs;                            // W1  one path per leg, in visiting order
    Cost   totalCost = 0;                              // W1
};

// Base class for every mode. Modes solve all at once; only C's plain shortest path animates.
class Problem {                                                   // W1
public:
    virtual ~Problem() = default;
    virtual std::string name() const = 0;
    void setStops(std::vector<NodeId> stops);                     // stops[0] = start
    void setPathfinder(std::unique_ptr<Pathfinder> pf);           // takes ownership; C gives each problem its own
    virtual ProblemResult solve(const Graph& g) = 0;
protected:
    std::vector<NodeId> stops_;
    std::unique_ptr<Pathfinder> pf_;
};

// Visits the stops in the given order
class WaypointProblem : public Problem {                          // W1
public:
    std::string name() const override;
    ProblemResult solve(const Graph& g) override;
};

}
