#version 450 core

out vec4 FragColor;
layout (location = 0) in vec3 aCol;
void main() {
  FragColor = vec4(aCol, 1.0f);
}

