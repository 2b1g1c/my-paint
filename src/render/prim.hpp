#pragma once

#include "pch.hpp"

namespace mr {
  class Prim {
  private:
    enum class TopologyType : std::uint32_t {
      eTrimesh = GL_TRIANGLES,
      ePoints = GL_POINTS,
      eTriStrip = GL_TRIANGLE_STRIP,
      ePatches = GL_PATCHES,
      eLines = GL_LINES
    };

    TopologyType _ttype = TopologyType::eTrimesh;
    std::uint32_t _num_of_instances = 1;
    std::uint32_t _vbuf, _ibuf, _va; /* vertex, index buffers, vertex array from the device */
    std::uint32_t _num_of_elements;  /* number of elements on the device */
    std::uint32_t _num_of_patches;   /* number of patches */

  public:
    template <typename V, typename I>
      Prim(std::span<V> vertices, std::span<I> indices) {
        /* Filling in given primitive parameters */
        if (vertices.size() != 0) {
          glGenVertexArrays(1, &_va);

          glGenBuffers(1, &_vbuf);

          glBindVertexArray(_va);
          glBindBuffer(GL_ARRAY_BUFFER, _vbuf);
          glBufferData(GL_ARRAY_BUFFER, sizeof(V) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

          /* Semantic merging */
          glVertexAttribPointer(0, sizeof(V) / sizeof(float), GL_FLOAT, false, sizeof(V), nullptr); // single Vec3f
          glEnableVertexAttribArray(0);

          glBindVertexArray(0);
          if (indices.size() != 0) {
            glGenBuffers(1, &_ibuf);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibuf);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(I) * indices.size(), indices.data(), GL_STATIC_DRAW);

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

    ~Prim() {
      glDeleteVertexArrays(1, &_va);
      glDeleteBuffers(1, &_vbuf);
      glDeleteBuffers(1, &_ibuf);
    }

    void draw() {
      glBindVertexArray(_va);

      if (_ibuf == 0) {
        glDrawArraysInstanced((uint32_t)_ttype, 0, _num_of_elements, _num_of_instances);
      }
      else {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibuf);
        glDrawElementsInstanced((uint32_t)_ttype, _num_of_elements, GL_UNSIGNED_INT, NULL, _num_of_instances);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      }

      /* Turning vertex array off */
      glBindVertexArray(0);
    }
  };
}
