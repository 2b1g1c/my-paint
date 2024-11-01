#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

#include "pch.hpp"
#include "prim.hpp"

namespace mr {
  class PrimCollection {
  public:
    enum class PrimType : std::uint32_t {
      eCircle = 0,
      eSquare = 1,
      eCloud  = 2, // point-cloud-like
    };

  private:
    std::vector<std::pair<PrimType, Prim>> _prims;

  public:
    PrimCollection() noexcept = default;

    Prim & add(PrimType type, Prim pr) noexcept;

    void draw() const noexcept;
  };
}
