#version 330 core

vec2 rotate(vec2 v, float a) {
	float s = sin(a);
	float c = cos(a);
	mat2 m = mat2(c, s, -s, c);
	return m * v;
}

layout (location = 0) in vec3 aPos;
void main() {
  gl_Position = vec4(rotate(aPos.xy, aPos.z), 0.0f, 1.0f);
}

