#pragma once

namespace mr {
  class SSBO {
    private:
      std::uint32_t ssbo = 0;

    public:
      SSBO() noexcept = default;

      template <typename T>
        SSBO(std::span<T> data) {
          glGenBuffers(1, &ssbo);
          write(data);
        }

      ~SSBO() {
        glDeleteBuffers(1, &ssbo);
      }

      void bind() const {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
      }

      static void unbind() {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
      }

      template <typename T>
      void write(std::span<T> data, std::uint32_t usage = GL_DYNAMIC_DRAW) {
        bind();
        glBufferData(GL_SHADER_STORAGE_BUFFER, data.size() * sizeof(T), data.data(), usage);
        unbind();
      }
  };
}
