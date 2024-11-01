#include "prim_coolection.hpp"

mr::Prim & mr::PrimCollection::add(PrimType type, Prim pr) noexcept {
  using ElemT = std::pair<PrimType, Prim>;
  auto less = [](const ElemT &lhs, const ElemT &rhs) -> bool {
    return (uint32_t)lhs.first < (uint32_t)rhs.first;
  };

  _prims.emplace_back(std::make_pair(type, std::move(pr)));
  std::sort(_prims.begin(), _prims.end(), less);

  return _prims.back().second;
}

void mr::PrimCollection::draw() const noexcept {
  for (const auto &p : _prims) {
    p.second.draw();
  }
}
