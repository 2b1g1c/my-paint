#include <filesystem>
#include <fstream>
#include <vector>

#include "rnd/shader.hpp"

std::vector<char> read_file(std::filesystem::path source)
{
  std::vector<char> res;
  std::ifstream input = std::ifstream(source);

  if (!input.is_open()) {
    std::cout << "Failed to open shader source" << std::endl;
    exit(102);
  }

  res.resize(std::filesystem::file_size(source));

  input.read(res.data(), res.size());

  if (res.back() != 0) {
    res.push_back(0);
  }

  return res;
}

std::vector<char> read_vert(std::string_view source_dir)
{
  return read_file(glb::exec_path / "bin" / "shaders" / source_dir /
                   "vert.glsl");
}

std::vector<char> read_frag(std::string_view source_dir)
{
  return read_file(glb::exec_path / "bin" / "shaders" / source_dir /
                   "frag.glsl");
}

mr::Shader::Shader(std::string_view source)
{
  std::vector<char> raw;

  // vertex shader
  raw = read_vert(source);
  char *v_sources[] {raw.data()};
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, v_sources, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "VERTEX SHADER COMPILATION ERROR:\n" << infoLog << std::endl;
  }

  // fragment shader
  raw = read_frag(source);
  char *f_sources[] {raw.data()};
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, f_sources, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "FRAGMENT SHADER COMPILATION ERROR:\n" << infoLog << std::endl;
  }

  // link shaders
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "SHADER LINKING ERROR\n" << infoLog << std::endl;
  }

  _vshd = vertexShader;
  _fshd = fragmentShader;
  _id = shaderProgram;
}
