#include "prim_coolection.hpp"

mr::Prim &mr::PrimCollection::add(Prim pr) noexcept
{
  _prims.emplace_back(std::move(pr));
  return _prims.back();
}

void mr::PrimCollection::draw() const noexcept
{
  for (const auto &p : _prims) { p.draw(); }
}
