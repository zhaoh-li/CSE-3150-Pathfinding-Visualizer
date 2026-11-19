#include "Graph.h"
#include <cassert>

namespace pf {

NodeId Graph::addNode(float x, float y) {
    NodeId id = static_cast<NodeId>(nodes_.size());
    nodes_.push_back({id, x, y});
    adj_.emplace_back();
    return id;
}

void Graph::addEdge(NodeId from, NodeId to, Cost w) {
    assert(from >= 0 && from < nodeCount());
    assert(to >= 0 && to < nodeCount());
    if (w <= 0) return;

    for (Edge& e : adj_[from]) {
        if (e.to == to) {
            if (w < e.weight) e.weight = w;
            return;
        }
    }
    adj_[from].push_back({to, w});
}

void Graph::addTwoWayEdge(NodeId a, NodeId b, Cost w) {
    addEdge(a, b, w);
    addEdge(b, a, w);
}

const Node& Graph::node(NodeId id) const {
    assert(id >= 0 && id < nodeCount());
    return nodes_[id];
}

const std::vector<Edge>& Graph::neighbors(NodeId id) const {
    assert(id >= 0 && id < nodeCount());
    return adj_[id];
}

int Graph::nodeCount() const { return static_cast<int>(nodes_.size()); }

GridGraph::GridGraph(int width, int height) : width_(width), height_(height) {
    assert(width >= 0 && height >= 0);
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            addNode(static_cast<float>(x), static_cast<float>(y));
}

NodeId GridGraph::id(int x, int y) const {
    assert(x >= 0 && x < width_ && y >= 0 && y < height_);
    return y * width_ + x;
}

std::pair<int, int> GridGraph::cell(NodeId id) const {
    assert(id >= 0 && id < width_ * height_);
    return {id % width_, id / width_};
}

int GridGraph::width() const { return width_; }
int GridGraph::height() const { return height_; }

}