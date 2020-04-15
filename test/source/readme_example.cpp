#include <doctest/doctest.h>

// clang-format off
#include <index_set.h>
#include <iostream>

void example() {
  // create index sets
  auto a = index_set::createIndexSetFromIndices({2, 4, 6});
  auto b = index_set::createIndexSetFromIndex(3);

  // add and remove single indices (slow)
  b.addIndex(6);
  a.removeIndex(4);

  // perform operations on index sets (very fast)
  a.remove(b);
  a.add(b);
  a.intersect(b);

  // iteration
  for (auto index: a.indices()) { 
    std::cout << index << std::endl;
  }

  // printing
  std::cout << a << std::endl;
}
// clang-format on

TEST_CASE("readme example compiles") { example(); }