[![Actions Status](https://github.com/TheLartians/IndexSet/workflows/MacOS/badge.svg)](https://github.com/TheLartians/IndexSet/actions)
[![Actions Status](https://github.com/TheLartians/IndexSet/workflows/Windows/badge.svg)](https://github.com/TheLartians/IndexSet/actions)
[![Actions Status](https://github.com/TheLartians/IndexSet/workflows/Ubuntu/badge.svg)](https://github.com/TheLartians/IndexSet/actions)
[![Actions Status](https://github.com/TheLartians/IndexSet/workflows/Style/badge.svg)](https://github.com/TheLartians/IndexSet/actions)
[![Actions Status](https://github.com/TheLartians/IndexSet/workflows/Install/badge.svg)](https://github.com/TheLartians/IndexSet/actions)
[![codecov](https://codecov.io/gh/TheLartians/IndexSet/branch/master/graph/badge.svg)](https://codecov.io/gh/TheLartians/IndexSet)

# IndexSet

A small library to work on large sets of indices with optimal memory and runtime performance.
Internally IndexSet is using the [BitLens](https://github.com/TheLartians/BitLens) library store indices as a bitmask vector.
Operations on index sets are performed on data values, which is [many orders of magnitude faster](https://github.com/TheLartians/BitLens#Benchmark) than comparing individual indices.

## Usage

You can easily add IndexSet through [CPM.cmake](https://github.com/TheLartians/CPM.cmake).

```cmake
CPMAddPackage(
  NAME IndexSet
  GITHUB_REPOSITORY TheLartians/IndexSet
  VERSION 0.1
)
```

## API

```cpp
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
```
