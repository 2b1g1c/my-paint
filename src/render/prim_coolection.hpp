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

      void emplace_back(mr::Prim other) noexcept {
        // draw func
        
        std::vector<mr::Prim>::emplace_back(std::move(other));
        // sync
      }

      void draw() const noexcept;
  };
} // namespace mr
