#version 450 core

struct Transform
{
  vec2 pos;
  float rot;
  float scale;
};

layout(std430, binding = 0) readonly buffer Transforms
{
  Transform transforms[];
};

vec2 rotate(vec2 v, float a) {
	float s = sin(a);
	float c = cos(a);
	mat2 m = mat2(c, s, -s, c);
	return m * v;
}

layout (location = 0) in vec2 aPos;

void main() {
  Transform transform = transforms[gl_InstanceID];
  vec2 translation = transform.pos;
  float rotation = transform.rot;
  float scale = transform.scale;

  gl_Position = vec4(translation + scale * rotate(aPos.xy, rotation), 0.0f, 1.0f);
}

