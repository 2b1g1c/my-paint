#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

#include "pch.hpp"
#include "prim.hpp"

namespace mr {
  class PrimCollection {
    private:
      std::vector<Prim> _prims;

    public:
      PrimCollection() noexcept = default;

      Prim& add(Prim pr) noexcept;

      void draw() const noexcept;

      auto size() const noexcept { return _prims.size(); }
  };
} // namespace mr
