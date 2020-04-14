#include <doctest/doctest.h>
#include <index_set.h>

#include <algorithm>
#include <sstream>

using namespace index_set;

TEST_CASE("equality") {
  CHECK(createIndexSetFromIndices({2, 5, 6}) == createIndexSetFromIndices({2, 5, 6}));
  CHECK(createIndexSetFromIndices({2, 5, 6}) != createIndexSetFromIndices({2, 4, 6}));
  CHECK(createIndexSetFromIndices({2, 5, 6}) != createIndexSetFromIndices({}));
  CHECK(createIndexSetFromIndices({42}) == createIndexSetFromIndex(42));
}

TEST_CASE("copy / move") {
  IndexSet a = createIndexSetFromIndices({1, 2, 3});
  IndexSet b;
  std::swap(a, b);
  CHECK(b == createIndexSetFromIndices({1, 2, 3}));
  CHECK(a == createIndexSetFromIndices({}));
  a = b;
  CHECK(a == b);
}

TEST_CASE("addIndex / hasIndex") {
  IndexSet indices;
  indices.addIndex(1);
  indices.addIndex(3);
  CHECK(!indices.hasIndex(0));
  CHECK(indices.hasIndex(1));
  CHECK(!indices.hasIndex(2));
  CHECK(indices.hasIndex(3));
  CHECK(!indices.hasIndex(indices.upperBound()));
}

TEST_CASE("removeIndex") {
  auto indices = createIndexSetFromIndices({1, 2, 3});
  indices.removeIndex(3);
  CHECK(indices == createIndexSetFromIndices({1, 2}));
}

TEST_CASE("upperBound") {
  auto indices = createIndexSetFromIndices({1, 42, 145});
  CHECK(indices.upperBound() == indices.bits().size());
}

TEST_CASE("add") {
  IndexSet indices = createIndexSetFromIndices({1, 2, 3, 6});
  indices.add(createIndexSetFromIndices({0, 3, 6, 9}));
  CHECK(indices == createIndexSetFromIndices({0, 1, 2, 3, 6, 9}));
}

TEST_CASE("remove") {
  IndexSet indices = createIndexSetFromIndices({1, 2, 3, 6});
  indices.remove(createIndexSetFromIndices({0, 3, 6, 9}));
  CHECK(indices == createIndexSetFromIndices({1, 2}));
}

TEST_CASE("intersect") {
  IndexSet indices = createIndexSetFromIndices({1, 2, 3, 6});
  indices.intersect(createIndexSetFromIndices({0, 3, 6, 9}));
  CHECK(indices == createIndexSetFromIndices({3, 6}));
}

TEST_CASE("isEmpty") {
  IndexSet indices = createIndexSetFromIndex(1);
  CHECK(!indices.isEmpty());
  indices.removeIndex(1);
  CHECK(indices.isEmpty());
}

TEST_CASE("clear") {
  IndexSet indices = createIndexSetFromIndices({1, 2, 3});
  REQUIRE(!indices.isEmpty());
  indices.clear();
  CHECK(indices.isEmpty());
}

TEST_CASE("count") {
  CHECK(createIndexSetFromIndices({}).count() == 0);
  CHECK(createIndexSetFromIndices({1}).count() == 1);
  CHECK(createIndexSetFromIndices({2, 5, 7, 8, 10}).count() == 5);
}

TEST_CASE("Printing") {
  std::stringstream stream;
  stream << createIndexSetFromIndices({1, 3, 4});
  CHECK(stream.str() == "[1,3,4]");
}
