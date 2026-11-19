#include "core/Algorithm.h"
#include "core/FindPath.h"
#include <cassert>
#include <iostream>

using namespace pf;

// 0 -> 1 -> 2 -> 3, weights 1, 2, 3
static void testStraightLine() {
    Graph g;
    for (int i = 0; i < 4; ++i) g.addNode();
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);

    BFS bfs;
    Path p = findPath(bfs, g, 0, 3);

    assert((p == Path{0, 1, 2, 3}));
    assert(bfs.stats().pathCost == 6);       // sum of real weights, worked out by hand
    assert(bfs.stats().pathLength == 3);     // edges, not nodes
    assert(bfs.stats().nodesExpanded == 4);  // 0, 1, 2, then the goal 3
    assert(!bfs.step());                     // step() after finishing stays false
}

int main() {
    testStraightLine();
    std::cout << "test_core: all passed\n";
}

// 0 -> 1, node 2 is cut off
static void testUnreachable() {
    Graph g;
    for (int i = 0; i < 3; ++i) g.addNode();
    g.addEdge(0, 1, 1);

    BFS bfs;
    assert(findPath(bfs, g, 0, 2).empty());
    assert(bfs.stats().pathCost == 0);
    assert(!bfs.step());
}

static void testStartEqualsGoal() {
    Graph g;
    g.addNode();
    g.addNode();
    g.addEdge(0, 1, 1);

    BFS bfs;
    assert((findPath(bfs, g, 1, 1) == Path{1}));
    assert(bfs.stats().pathLength == 0);
    assert(!bfs.step());
}

static void testInvalidIds() {
    Graph g;
    g.addNode();
    g.addNode();
    g.addEdge(0, 1, 1);

    BFS bfs;
    assert(findPath(bfs, g, -1, 1).empty());   // no crash, empty path
    assert(findPath(bfs, g, 0, -1).empty());
    assert(findPath(bfs, g, 0, 99).empty());
    assert((findPath(bfs, g, 0, 1) == Path{0, 1}));   // start() again resets everything
}