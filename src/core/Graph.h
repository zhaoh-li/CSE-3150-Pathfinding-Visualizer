#pragma once
#include "Types.h"
#include <utility>
#include <vector>

namespace pf {

struct Node { NodeId id; float x, y; };          // W1  walls are nodes with no edges
struct Edge { NodeId to; Cost weight; };         // W1

// Node IDs passed in must be valid (assert)
class Graph {
public:
    NodeId addNode(float x = 0.0f, float y = 0.0f);               // W1  returns the new ID
    void   addEdge(NodeId from, NodeId to, Cost w);               // W1  one-way; ignores w <= 0; a duplicate keeps the
                                                                  //     cheaper weight
    void   addTwoWayEdge(NodeId a, NodeId b, Cost w);             // W1
    const Node& node(NodeId id) const;                            // W1
    const std::vector<Edge>& neighbors(NodeId id) const;          // W1
    int    nodeCount() const;                                     // W1
private:
    std::vector<Node> nodes_;
    std::vector<std::vector<Edge>> adj_;                          // open edges leaving each node
};

class GridGraph : public Graph {                  // W1
public:
    GridGraph(int width, int height);             // width * height nodes at x, y = their cell, no edges yet
    NodeId id(int x, int y) const;                // y * width + x; cell must be inside (assert)
    std::pair<int, int> cell(NodeId id) const;    // the reverse of id()
    int width() const;
    int height() const;
private:
    int width_, height_;
};

}
