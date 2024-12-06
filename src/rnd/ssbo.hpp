#pragma once

namespace mr {
  template <typename T>
    class SSBO {
      private:
        std::uint32_t _ssbo = 0;
        std::uint32_t _size = 0;

      public:
        inline static uint32_t bindpoint = 0;

        SSBO() noexcept = default;

        SSBO(SSBO &&other) noexcept {
          std::swap(_ssbo, other._ssbo);
          std::swap(_size, other._size);
        }
        SSBO& operator=(SSBO &&other) noexcept {
          std::swap(_ssbo, other._ssbo);
          std::swap(_size, other._size);
          return *this;
        }

        SSBO(const std::vector<T> &data) {
          _size = data.size();
          glGenBuffers(1, &_ssbo);
          glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
          glBufferData(GL_SHADER_STORAGE_BUFFER, data.size() * sizeof(T), data.data(), GL_DYNAMIC_COPY);
          glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        }

        ~SSBO() {
          glDeleteBuffers(1, &_ssbo);
        }

        void update(const std::vector<T> &data) noexcept {
          _size = data.size();
          glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
          glBufferData(GL_SHADER_STORAGE_BUFFER, data.size() * sizeof(T), data.data(), GL_DYNAMIC_COPY);
          glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        }

        void apply() const noexcept {
          glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _ssbo);
        }

        size_t size() const noexcept {
          return _size;
        }
    };
}
