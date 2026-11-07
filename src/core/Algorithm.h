#pragma once
#include "Graph.h"
#include "RunStats.h"
#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <vector>

namespace pf {

enum class NodeState { Unvisited, Frontier, Visited, Path };        // W1

// Base class for every algorithm. Follows "Rules every search follows" in TODO_A.md (team plan).
class Pathfinder {                                                   // W1
public:
    virtual ~Pathfinder() = default;
    virtual std::string name() const = 0;
    virtual void start(const Graph& g, NodeId start, NodeId goal) = 0;  // resets everything
    virtual bool step() = 0;                                           // one node; false once finished
    NodeState state(NodeId id) const;
    Path path() const;
    const RunStats& stats() const;
protected:
    void reset(const Graph& g, NodeId start, NodeId goal);
    void buildPath();                                                  // follows parent_ back from the goal
    const Graph* graph_ = nullptr;
    NodeId start_ = -1, goal_ = -1;
    std::vector<NodeState> states_;
    std::vector<NodeId> parent_;
    RunStats stats_;
};

class BFS : public Pathfinder {                                        // W1
public:
    std::string name() const override;
    void start(const Graph& g, NodeId start, NodeId goal) override;
    bool step() override;
private:
    std::queue<NodeId> frontier_;
};

class Dijkstra : public Pathfinder {                                   // W1
public:
    std::string name() const override;
    void start(const Graph& g, NodeId start, NodeId goal) override;
    bool step() override;
protected:
    std::vector<Cost> dist_;
    std::priority_queue<std::pair<Cost, NodeId>,
                        std::vector<std::pair<Cost, NodeId>>,
                        std::greater<>> frontier_;
};

// Keeps these two functions all project long.
class PathfinderFactory {                                              // W1
public:
    static std::unique_ptr<Pathfinder> create(const std::string& name);   // nullptr if unknown
    static std::vector<std::string> names();                              // W1: BFS, Dijkstra
};

}
