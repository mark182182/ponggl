#version 330 core
// x y normalx normaly texturecoord texturecoord
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aNormal;
layout (location = 2) in vec2 textCoords;

out vec2 TexCoords;
out vec2 FragPos;
out vec2 Normal;

uniform mat4 model;
uniform mat4 projection;

void main()
{
  gl_Position = projection * model * vec4(aPos, 0.0, 1.0);
  TexCoords = textCoords;
  FragPos = vec2(model * vec4(aPos, 0.0, 1.0));
  Normal = aNormal;
}