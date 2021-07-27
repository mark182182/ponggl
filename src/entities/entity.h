#ifndef ENTITY_H
#define ENTITY_H

#include "../shaders/shader.h"
#include "../texture.h"
#include <iostream>
#include <string>
#include <glad/glad.h>

class Entity
{
  unsigned int vbo, vao, ebo;
  float vertices[6][4] = {{0.0f, 0.4f, 0.0f, 1.0f},
                          {0.2f, 0.0f, 1.0f, 0.0f},
                          {0.0f, 0.0f, 0.0f, 0.0f},
                          {0.0f, 0.4f, 0.0f, 1.0f},
                          {0.2f, 0.4f, 1.0f, 1.0f},
                          {0.2f, 0.0f, 1.0f, 0.0f}};

public:
  std::string name;
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 projection;
  glm::vec3 scale = glm::vec3(1.0f, 1.0f, 0.0f);
  glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 normPos = glm::normalize(position);
  Texture texture;
  float speed = 0.01f;
  Shader shader;
  Entity(){};
  ~Entity(){};
  Entity(std::string entity_name, Shader &s, glm::mat4 proj, glm::vec2 _scale, glm::vec2 pos, Texture &_texture)
  {
    name = std::string(entity_name);
    scale = glm::vec3(_scale, 0.0f);
    shader = s;
    projection = proj;
    texture = _texture;
    update_position(pos);
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    bind_buffers();
  };

  void bind()
  {
    glBindVertexArray(vao);
  }

  void draw()
  {
    glDrawArrays(GL_TRIANGLES, 0, 6);
  }

  void unbind()
  {
    glBindVertexArray(0);
  }

  void delete_buffers()
  {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
  }

  void update_position(glm::vec2 &pos)
  {
    position = glm::vec3(pos, 0.0f);
    normPos = glm::normalize(position);
  }

  void update_scale(glm::vec2 &s)
  {
    scale = glm::vec3(s, 0.0f);
  }

  void bind_buffers()
  {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  void handle_logic()
  {
    std::cout << "basic entity logic"
              << "\r\n";
  };

  void handle_logic(Entity &e){};
};

// AABB - AABB
bool check_collision(Entity &one, Entity &two)
{
  bool isCollidingX = one.position.x + one.scale.x / 4 >= two.position.x && two.position.x + two.scale.x / 4 >= one.position.x;
  bool isCollidingY = one.position.y + one.scale.y / 2.5 >= two.position.y && two.position.y + two.scale.y / 2.5 >= one.position.y;
  return isCollidingX && isCollidingY;
}

#endif