#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

#include "pch.hpp"
#include "prim.hpp"

namespace mr {
  class PrimCollection : public std::vector<Prim> {
    public:
      PrimCollection() noexcept = default;

      void draw() const noexcept;
  };
} // namespace mr
