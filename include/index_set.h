#pragma once

#include <bit_lens.h>

#include <ostream>
#include <vector>

namespace index_set {

  struct IndexSet {
  public:
    using Data = std::vector<unsigned int>;
    using Index = size_t;

  private:
    Data data;

  public:
    bit_lens::BitLens<Data> bits();
    bit_lens::BitLens<const Data> bits() const;

    void ensureFits(Index idx);
    void addIndex(Index idx);
    void tighten();
    bool hasIndex(Index idx) const;
    void remove(const IndexSet &other);
    void clear();
    size_t upperBound() const;
    size_t count() const;
    void intersect(const IndexSet &other);
    void add(const IndexSet &other);
    bool isEmpty() const;
    bool operator==(const IndexSet &) const;
    bool operator!=(const IndexSet &) const;
  };

  IndexSet createIndexSetFromIndex(IndexSet::Index idx);
  IndexSet createIndexSetFromIndices(const std::vector<IndexSet::Index> &input);

  std::ostream &operator<<(std::ostream &, const IndexSet &);

}  // namespace index_set