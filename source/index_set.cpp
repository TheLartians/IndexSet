#include <index_set.h>
#include <easy_iterator.h>

using namespace index_set;

IndexSet index_set::createIndexSetFromIndex(IndexSet::Index idx) {
  IndexSet IndexSet;
  IndexSet.addIndex(idx);
  return IndexSet;
}

IndexSet index_set::createIndexSetFromIndices(const std::vector<IndexSet::Index> &input) {
  IndexSet IndexSet;
  for (auto idx : input) {
    IndexSet.addIndex(idx);
  }
  return IndexSet;
}

bit_lens::Lens<IndexSet::Data> IndexSet::bits() {
  return bit_lens::BitLens(data);
}

bit_lens::Lens<const IndexSet::Data> IndexSet::bits() const {
  return bit_lens::BitLens(data);
}


bool IndexSet::operator==(const IndexSet &other) const {
  return this->data == other.data;
}

bool IndexSet::operator!=(const IndexSet &other) const {
  return this->data != other.data;
}

void IndexSet::ensureFits(Index idx) {
  if (bits().size() <= idx) {
    bits().resize(idx + 1, 0);
  }
}

void IndexSet::addIndex(Index idx) {
  ensureFits(idx);
  bits()[idx] = true;
}

size_t IndexSet::upperBound() const { return bits().size(); }

bool IndexSet::hasIndex(Index idx) const {
  if (idx >= bits().size()) {
    return false;
  } else {
    return bits()[idx];
  }
}

bool IndexSet::isEmpty() const { return data.size() == 0; }

void IndexSet::clear() { data.clear(); }

void IndexSet::remove(const IndexSet &other) {
  auto N = std::min(data.size(), other.data.size());
  for (size_t i = 0; i < N; ++i) {
    data[i] = data[i] & ~other.data[i];
  }
  tighten();
}

void IndexSet::intersect(const IndexSet &other) {
  auto N = std::min(data.size(), other.data.size());
  data.resize(N, 0);
  for (size_t i = 0; i < N; ++i) {
    data[i] = data[i] & other.data[i];
  }
  tighten();
}

void IndexSet::add(const IndexSet &other) {
  if (data.size() < other.data.size()) data.resize(other.data.size());
  for (size_t i = 0; i < other.data.size(); ++i) {
    data[i] = data[i] | other.data[i];
  }
}

void IndexSet::tighten() {
  if (data.size() == 0) return;
  size_t i = data.size(), N = i;
  while (i-- > 0 && data[i] == 0) N = i;
  data.resize(N);
}

size_t IndexSet::count() const {
  size_t result = 0;
  for (auto b : bits()) {
    if (b) result++;
  }
  return result;
}

std::ostream &index_set::operator<<(std::ostream &stream, const IndexSet &indices) {
  stream << '[';
  bool separator = false;

  for (auto [i, v] : easy_iterator::enumerate(indices.bits())) {
    if (v) {
      if (separator) stream << ',';
      stream << i;
      separator = true;
    }
  }

  stream << ']';
  return stream;
}
