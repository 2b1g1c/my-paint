#include "prim_coolection.hpp"
#include "app/app.hpp"
#include "prim.hpp"

void mr::PrimCollection::draw() const noexcept
{
  for (const auto &p : *this) { p.draw(); }
}


void mr::PrimCollection::emplace_back(mr::Application &app, mr::Prim other) noexcept {
  // draw func
  std::string str_object = mr::prim_to_json(other);
  app.sync_object(str_object);
  std::vector<Prim>::emplace_back(std::move(other));
  // sync
}
