#include <doctest/doctest.h>
#include <index_set.h>

#include <sstream>

TEST_CASE("Basic operations") {
  using namespace index_set;

  IndexSet indices;
  indices.addIndex(45);
  CHECK(indices.upperBound() == indices.bits().size());
  CHECK(indices.hasIndex(45));
  CHECK(!indices.hasIndex(46));
  CHECK(indices.hasIndex(indices.upperBound()) == false);
  CHECK(!indices.isEmpty());
  CHECK(indices == createIndexSetFromIndex(45));
  CHECK(indices != createIndexSetFromIndex(44));
  indices.add(createIndexSetFromIndices({3, 99}));
  CHECK(indices == createIndexSetFromIndices({3, 45, 99}));
  indices.remove(createIndexSetFromIndices({1, 2, 45, 99}));
  CHECK(indices == createIndexSetFromIndices({3}));
  indices.add(createIndexSetFromIndices({2, 3, 4, 5}));
  CHECK(indices == createIndexSetFromIndices({2, 3, 4, 5}));
  CHECK(indices.count() == 4);
  indices.intersect(createIndexSetFromIndices({0, 4, 5, 6, 7}));
  CHECK(indices == createIndexSetFromIndices({4, 5}));
  indices.clear();
  CHECK(indices == createIndexSetFromIndices({}));
  CHECK(indices.isEmpty());
}

TEST_CASE("Printing") {
  std::stringstream stream;
  stream << index_set::createIndexSetFromIndices({1, 3, 4});
  CHECK(stream.str() == "[1,3,4]");
}
