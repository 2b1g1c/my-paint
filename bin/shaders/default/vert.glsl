#version 330 core

uniform vec2 translation;
uniform float rotation;
uniform float scale;

vec2 rotate(vec2 v, float a) {
	float s = sin(a);
	float c = cos(a);
	mat2 m = mat2(c, s, -s, c);
	return m * v;
}

layout (location = 0) in vec2 aPos;
void main() {
  gl_Position = vec4(translation + scale * rotate(aPos.xy, rotation), 0.0f, 1.0f);
}

