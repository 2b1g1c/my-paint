#pragma once

#include "pch.hpp"

namespace mr {
  class Shader {
    private:
      std::uint32_t _vshd = 0;
      std::uint32_t _fshd = 0;
      std::uint32_t _id = 0;

    public:
      Shader() noexcept = default;
      Shader(std::string_view source);

      // getters
      std::uint32_t id() const { return _id; }

      // copy semantic
      Shader(const Shader &) = default;
      Shader &operator=(const Shader &) = default;

      // move semantic
      Shader(Shader &&other) noexcept
      {
        std::swap(_vshd, other._vshd);
        std::swap(_fshd, other._fshd);
        std::swap(_id, other._id);
      }

      Shader &operator=(Shader &&other)
      {
        std::swap(_vshd, other._vshd);
        std::swap(_fshd, other._fshd);
        std::swap(_id, other._id);
        return *this;
      }

      ~Shader()
      {
        if (_id == 0) {
          return;
        }

        glDetachShader(_id, _vshd);
        glDeleteShader(_vshd);

        glDetachShader(_id, _fshd);
        glDeleteShader(_fshd);

        glDeleteProgram(_id);
      }

      void bind() const noexcept { glUseProgram(_id); }
  };
} // namespace mr
