#pragma once

#include "pch.hpp"

namespace mr {
  class Shader {
  private:
    int _id;

  public:
    Shader() noexcept = default;
    Shader(std::string_view source);

    ~Shader() {
      glDeleteProgram(_id);
    }

    void bind() {
      glUseProgram(_id);
    }
  };
}
