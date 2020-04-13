#include <doctest/doctest.h>
#include <index_set.h>

#include <sstream>

TEST_CASE("Basic operations") {
  using namespace index_set;

  IndexSet index;
  index.addIndex(45);
  CHECK(== index.bits().size());
  CHECK(index.hasIndex(45));
  CHECK(!index.hasIndex(46));
  CHECK(index.hasIndex(index.upperBound()) == false);
  CHECK(!index.isEmpty());
  CHECK(index == createIndexSetFromIndex(45));
  CHECK(index != createIndexSetFromIndex(44));
  index.add(createIndexSetFromIndices({3, 99}));
  CHECK(index == createIndexSetFromIndices({3, 45, 99}));
  index.remove(createIndexSetFromIndices({1, 2, 45, 99}));
  CHECK(index == createIndexSetFromIndices({3}));
  index.add(createIndexSetFromIndices({2, 3, 4, 5}));
  CHECK(index == createIndexSetFromIndices({2, 3, 4, 5}));
  CHECK(index.count() == 4);
  index.intersect(createIndexSetFromIndices({0, 4, 5, 6, 7}));
  CHECK(index == createIndexSetFromIndices({4, 5}));
  index.clear();
  CHECK(index == createIndexSetFromIndices({}));
  CHECK(index.isEmpty());
}

TEST_CASE("Printing") {
  std::stringstream stream;
  stream << createIndexSetFromIndices({1, 3, 4});
  CHECK(stream.str() == "[1,3,4]");
}
