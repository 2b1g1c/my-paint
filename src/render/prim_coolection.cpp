#include "prim_coolection.hpp"

void mr::PrimCollection::draw() const noexcept
{
  for (const auto &p : *this) { p.draw(); }
}


void mr::PrimCollection::emplace_back(mr::Application &app, mr::Prim other) noexcept {
  // draw func
        
  std::vector<Prim>::emplace_back(std::move(other));
  // sync
}
