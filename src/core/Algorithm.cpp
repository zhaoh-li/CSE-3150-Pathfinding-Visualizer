#include "Algorithm.h"
#include <algorithm>
#include <cassert>

namespace pf {

// ---- Pathfinder base ----

NodeState Pathfinder::state(NodeId id) const {
    assert(id >= 0 && id < static_cast<int>(states_.size()));
    return states_[id];
}

Path Pathfinder::path() const { return path_; }

const RunStats& Pathfinder::stats() const { return stats_; }

void Pathfinder::reset(const Graph& g, NodeId start, NodeId goal) {
    graph_ = &g;
    start_ = start;
    goal_ = goal;
    states_.assign(g.nodeCount(), NodeState::Unvisited);
    parent_.assign(g.nodeCount(), -1);
    path_.clear();
    finished_ = false;
    stats_ = RunStats{};
}

bool Pathfinder::validEndpoints() const {
    int n = graph_->nodeCount();
    return start_ >= 0 && start_ < n && goal_ >= 0 && goal_ < n;
}

void Pathfinder::buildPath() {
    // Walk back from the goal to the start, then flip so the start comes first.
    path_.clear();
    for (NodeId n = goal_; n != -1; n = parent_[n]) path_.push_back(n);
    std::reverse(path_.begin(), path_.end());

    // pathCost is the sum of real edge weights, whatever the algorithm counts internally.
    Cost total = 0;
    for (std::size_t i = 0; i + 1 < path_.size(); ++i) {
        for (const Edge& e : graph_->neighbors(path_[i])) {
            if (e.to == path_[i + 1]) { total += e.weight; break; }
        }
    }
    stats_.pathCost = total;
    stats_.pathLength = static_cast<int>(path_.size()) - 1;   // edges, not nodes
    for (NodeId n : path_) states_[n] = NodeState::Path;
}

// ---- BFS ----

std::string BFS::name() const { return "BFS"; }

void BFS::start(const Graph& g, NodeId start, NodeId goal) {
    reset(g, start, goal);
    frontier_ = std::queue<NodeId>();            // clear leftovers from an earlier run

    if (!validEndpoints()) { finished_ = true; return; }
    if (start == goal) {
        path_ = {start};
        finished_ = true;
        states_[start] = NodeState::Path;
        return;
    }
    states_[start] = NodeState::Frontier;
    frontier_.push(start);
}

bool BFS::step() {
    if (finished_) return false;
    if (frontier_.empty()) { finished_ = true; return false; }

    NodeId current = frontier_.front();
    frontier_.pop();
    states_[current] = NodeState::Visited;
    ++stats_.nodesExpanded;

    // Stop when the goal is taken off the frontier, not when it is first seen.
    if (current == goal_) {
        buildPath();
        finished_ = true;
        return false;
    }

    for (const Edge& e : graph_->neighbors(current)) {
        // Nodes are marked Frontier when queued, so no node is queued twice
        // and the queue never holds stale entries.
        if (states_[e.to] == NodeState::Unvisited) {
            states_[e.to] = NodeState::Frontier;
            parent_[e.to] = current;
            frontier_.push(e.to);
        }
    }
    if (frontier_.empty()) finished_ = true;     // explored everything, goal unreachable
    return !finished_;
}

// ---- Factory ----

std::unique_ptr<Pathfinder> PathfinderFactory::create(const std::string& name) {
    if (name == "BFS") return std::make_unique<BFS>();
    return nullptr;
}

std::vector<std::string> PathfinderFactory::names() { return {"BFS"}; }

}