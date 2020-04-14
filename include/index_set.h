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
    void tighten();

  public:
    bit_lens::BitLens<Data> bits();
    bit_lens::BitLens<const Data> bits() const;

    void ensureFits(Index idx);

    bool hasIndex(Index idx) const;
    void addIndex(Index idx);
    void removeIndex(Index idx);

    void add(const IndexSet &other);
    void remove(const IndexSet &other);
    void intersect(const IndexSet &other);
    void clear();

    size_t upperBound() const;
    bool isEmpty() const;
    size_t count() const;

    bool operator==(const IndexSet &) const;
    bool operator!=(const IndexSet &) const;
  };

  IndexSet createIndexSetFromIndex(IndexSet::Index idx);
  IndexSet createIndexSetFromIndices(const std::vector<IndexSet::Index> &input);

  std::ostream &operator<<(std::ostream &, const IndexSet &);

}  // namespace index_set