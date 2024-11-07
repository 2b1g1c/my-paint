#include "prim_coolection.hpp"

void mr::PrimCollection::draw() const noexcept
{
  for (const auto &p : *this) { p.draw(); }
}
