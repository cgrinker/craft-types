#include "catch2/catch.hpp"

#include "shared.h"

#include "types/utility/graph/graph.hpp"

#include <string>

using namespace graph;
using namespace Catch::Matchers;


TEST_CASE( "graph::findNode", "[graph::findNode]" )
{
    Graph< GraphCore<std::string> > g;

    g.addNode("test");

    CHECK(findNode(g, "test") != nullptr);
    CHECK(findNode(g, "not-test") == nullptr);
}
