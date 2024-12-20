#pragma once

#include <algorithm>
#include <cstdint>
#include <array>

#include "pch.hpp"
#include "prim.hpp"
#include "shader.hpp"
#include "ssbo.hpp"

namespace mr {
  class Application;

  class PrimCollection {
    private:
      inline static constexpr std::size_t _size = (std::size_t)Prim::PrimType::eOther;

      std::array<Prim, _size> _prims;
      std::array<SSBO<ShapeData>, _size> _ssbos;
      std::array<std::vector<ShapeData>, _size> _datas;

    public:
      PrimCollection() noexcept = default;

      void emplace_back(mr::Prim::PrimType ptype, mr::ShapeData transform) noexcept;
      void emplace_back_synced(mr::Application &app, mr::Prim::PrimType ptype, mr::ShapeData transform) noexcept;

      void deserialize(const std::string &str);

      void draw() const noexcept;

      // getters
      constexpr std::size_t size() const noexcept { return _size; }
      constexpr const std::vector<ShapeData> & transforms(std::size_t i) const noexcept { return _datas[i]; }
  };
} // namespace mr
