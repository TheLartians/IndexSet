#pragma once

#include <bit_lens.h>
#include <easy_iterator.h>

#include <ostream>
#include <vector>

namespace index_set {

  struct IndexSet {
  public:
    using Data = std::vector<unsigned int>;
    using Bits = bit_lens::BitLens<Data>;
    using ConstBits = bit_lens::BitLens<const Data>;
    using Index = size_t;

    struct IndexIterator : public easy_iterator::InitializedIterable {
      Index current, max;
      ConstBits bits;
      IndexIterator(IndexSet::Index c, IndexSet::Index m, IndexSet::ConstBits b)
          : current(c), max(m), bits(b) {}

      void fit() {
        while (current != max && !bits[current]) ++current;
      }

      bool init() {
        fit();
        return current != max;
      }

      bool advance() {
        ++current;
        fit();
        return current != max;
      }

      IndexSet::Index value() const { return current; }
    };

  private:
    Data data;
    void tighten();

  public:
    Bits bits();
    ConstBits bits() const;

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

    auto indices() const {
      return easy_iterator::MakeIterable<IndexIterator>(0, upperBound(), bits());
    }
  };

  IndexSet createIndexSetFromIndex(IndexSet::Index idx);
  IndexSet createIndexSetFromIndices(const std::vector<IndexSet::Index> &input);

  std::ostream &operator<<(std::ostream &, const IndexSet &);

}  // namespace index_set
