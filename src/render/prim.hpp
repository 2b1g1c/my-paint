#pragma once

#include "pch.hpp"
#include "render/shader.hpp"

namespace mr {
  class Prim;

  Prim create_circle(float posx, float poxy, float r) noexcept;
  Prim create_square(float posx, float poxy, float a) noexcept;

  std::string prim_to_json(const Prim &other);
  Prim prim_from_json(const std::string &str);

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
      std::uint32_t _num_of_instances = 1;
      // vertex, index buffers, vertex array from the device
      std::uint32_t _vbuf = 0, _ibuf = 0, _va = 0;
      std::uint32_t _num_of_elements = 0; // number of elements on the device
      std::uint32_t _num_of_patches = 0;  // number of patches

      Shader shader;

      float p[2] = {}; // pos
      float a = 0;     // angle
      float s = 1;     // scale
      PrimType _ptype = PrimType::eOther;

    public:
      Prim() noexcept = default;

      // move semantic
      Prim(Prim&& other) noexcept
      {
        std::swap(_vbuf, other._vbuf);
        std::swap(_ibuf, other._ibuf);
        std::swap(_va, other._va);
        std::swap(shader, other.shader);
        std::swap(_ttype, other._ttype);
        std::swap(_num_of_instances, other._num_of_instances);
        std::swap(_num_of_elements, other._num_of_elements);
        std::swap(_num_of_patches, other._num_of_patches);
        std::swap(p[0], other.p[0]);
        std::swap(p[1], other.p[1]);
        std::swap(a, other.a);
        std::swap(s, other.s);
        std::swap(_ptype, other._ptype);
      }

      Prim& operator=(Prim&& other) noexcept
      {
        std::swap(_vbuf, other._vbuf);
        std::swap(_ibuf, other._ibuf);
        std::swap(_va, other._va);
        std::swap(shader, other.shader);
        std::swap(_ttype, other._ttype);
        std::swap(_num_of_instances, other._num_of_instances);
        std::swap(_num_of_elements, other._num_of_elements);
        std::swap(_num_of_patches, other._num_of_patches);
        std::swap(p[0], other.p[0]);
        std::swap(p[1], other.p[1]);
        std::swap(a, other.a);
        std::swap(s, other.s);
        std::swap(_ptype, other._ptype);
        return *this;
      }

      template <typename V, typename I>
      Prim(std::string_view source, std::span<V> vertices, std::span<I> indices,
           float posx = 0, float posy = 0, float angle = 0, float scale = 1, PrimType ptype = PrimType::eOther)
      {
        shader = mr::Shader(source);
        p[0] = posx;
        p[1] = posy;
        a = angle;
        s = scale;
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

      void draw() const noexcept;

      // getters
      float posx() const { return p[0]; }

      float& posx() { return p[0]; }

      float posy() const { return p[1]; }

      float& posy() { return p[1]; }

      float rot() const { return a; }

      float& rot() { return a; }

      float scale() const { return s; }

      float& scale() { return s; }

      PrimType ptype() const { return _ptype; }

      PrimType& ptype() { return _ptype; }
  };

  template <typename V>
    inline mr::Prim create_from_points(std::span<V> vertices) noexcept
    {
      // TODO: implement (via triangulation (on GPU???))
      return mr::Prim();
    }
} // namespace mr
