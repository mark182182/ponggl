#version 330 core

in vec2 TexCoords;
in vec2 FragPos;
in vec2 Normal;

out vec4 color;

uniform sampler2D image;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
  float ambientStrength = 0.6;
  vec3 ambient = ambientStrength * lightColor;

  vec3 lightDir = normalize(lightPos - vec3(FragPos, 0.0));
  
  float diff = max(dot(vec3(Normal, 0.0), lightDir), 0.0);
  vec3 diffuse = diff * lightColor;

  vec3 result = (ambient + diffuse) * objectColor;

  color = vec4(result, 1.0) * texture(image, TexCoords);
}