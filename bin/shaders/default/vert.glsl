#version 450 core

struct ShapeData
{
  vec4 color;
  vec2 pos;
  float rot;
  float scale;
};

layout(std430, binding = 0) readonly buffer Datas
{
  ShapeData shapedatas[];
};

vec2 rotate(vec2 v, float a) {
	float s = sin(a);
	float c = cos(a);
	mat2 m = mat2(c, s, -s, c);
	return m * v;
}

layout (location = 0) in vec2 aPos;
layout (location = 0) out vec3 aCol;

void main() {
  ShapeData shapedata = shapedatas[gl_InstanceID];
  vec4 color = shapedata.color;
  vec2 translation = shapedata.pos;
  float rotation = shapedata.rot;
  float scale = shapedata.scale;

  aCol = color.xyz; // vec3(102.f / 256.f, 47.f / 256.f, 30.f / 256.f);
  gl_Position = vec4(translation + scale * rotate(aPos.xy, rotation), 0.0f, 1.0f);
}

