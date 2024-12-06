#pragma once

#include "pch.hpp"
#include "rnd/ssbo.hpp"

namespace mr {
  struct Transform {
    float p[2] = {}; // pos
    float a = 0;     // angle
    float s = 1;     // scale

    float & posx() noexcept { return p[0]; }
    float & posy() noexcept { return p[1]; }
    float & rot() noexcept { return a; }
    float & scale() noexcept { return s; }

    float posx() const noexcept { return p[0]; }
    float posy() const noexcept { return p[1]; }
    float rot() const noexcept { return a; }
    float scale() const noexcept { return s; }
  };

  class Shader;

  class Prim {
    private:
      enum class TopologyType : std::uint32_t {
        eTrimesh  = GL_TRIANGLES,
        ePoints   = GL_POINTS,
        eTriStrip = GL_TRIANGLE_STRIP,
        ePatches  = GL_PATCHES,
        eLines    = GL_LINES
      };

    public:
      enum class PrimType : std::uint32_t {
        eCircle = 0,
        eSquare = 1,
        eOther = 2
      };

    private:
      TopologyType _ttype = TopologyType::eTrimesh;
      // vertex, index buffers, vertex array from the device
      std::uint32_t _vbuf = 0, _ibuf = 0, _va = 0;
      std::uint32_t _num_of_elements = 0; // number of elements on the device
      std::uint32_t _num_of_patches = 0;  // number of patches

      PrimType _ptype = PrimType::eOther;

    public:
      Prim() noexcept = default;

      // move semantic
      Prim(Prim&& other) noexcept
      {
        std::swap(_vbuf, other._vbuf);
        std::swap(_ibuf, other._ibuf);
        std::swap(_va, other._va);
        std::swap(_ttype, other._ttype);
        std::swap(_num_of_elements, other._num_of_elements);
        std::swap(_num_of_patches, other._num_of_patches);
        std::swap(_ptype, other._ptype);
      }

      Prim& operator=(Prim&& other) noexcept
      {
        std::swap(_vbuf, other._vbuf);
        std::swap(_ibuf, other._ibuf);
        std::swap(_va, other._va);
        std::swap(_ttype, other._ttype);
        std::swap(_num_of_elements, other._num_of_elements);
        std::swap(_num_of_patches, other._num_of_patches);
        std::swap(_ptype, other._ptype);
        return *this;
      }

      template <typename V, typename I>
      Prim(std::string_view source, std::span<V> vertices, std::span<I> indices, PrimType ptype = PrimType::eOther)
      {
        _ptype = ptype;

        if (vertices.size() != 0) {
          glGenVertexArrays(1, &_va);

          glGenBuffers(1, &_vbuf);

          glBindVertexArray(_va);
          glBindBuffer(GL_ARRAY_BUFFER, _vbuf);
          glBufferData(GL_ARRAY_BUFFER,
                       sizeof(V) * vertices.size(),
                       vertices.data(),
                       GL_STATIC_DRAW);

          /* Semantic merging */
          glVertexAttribPointer(0,
                                sizeof(V) / sizeof(float),
                                GL_FLOAT,
                                false,
                                sizeof(V),
                                nullptr); // single Vec3f
          glEnableVertexAttribArray(0);

          glBindVertexArray(0);
          if (indices.size() != 0) {
            glGenBuffers(1, &_ibuf);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibuf);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         sizeof(I) * indices.size(),
                         indices.data(),
                         GL_STATIC_DRAW);

            _num_of_elements = indices.size();
          }
          else {
            _num_of_elements = vertices.size();
          }
        }
        else {
          _num_of_elements = vertices.size();
        }
      }

      ~Prim() noexcept;

      void draw(const SSBO<Transform> &ssbo) const noexcept;

      // getters
      PrimType ptype() const { return _ptype; }

      PrimType & ptype() { return _ptype; }
  };

  Prim create_circle() noexcept;
  Prim create_square() noexcept;

  std::string serialize(mr::Prim::PrimType ptype, mr::Transform transform);
} // namespace mr
