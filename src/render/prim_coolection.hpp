#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

#include "pch.hpp"
#include "prim.hpp"

namespace mr {
  class Application;
  class PrimCollection : public std::vector<Prim> {
    public:
      PrimCollection() noexcept = default;
      void emplace_back(mr::Application &app, mr::Prim other) noexcept;

      void draw() const noexcept;
  };
} // namespace mr
