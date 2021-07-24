#ifndef ENTITY_H
#define ENTITY_H

#include "../shaders/shader.h"
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
  Shader shader;
  Entity(){};
  ~Entity(){};
  Entity(std::string entity_name, Shader &s, glm::mat4 proj, glm::vec2 size, glm::vec2 pos)
  {
    name = std::string(entity_name);
    scale = glm::vec3(size.x, size.y, 0.0f);
    shader = s;
    projection = proj;
    updatePosition(pos);
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

  void updatePosition(glm::vec2 pos)
  {
    position = glm::vec3(pos.x, pos.y, 0.0f);
    normPos = glm::normalize(position);
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
  bool isCollidingY = one.position.y + one.scale.y / 3 >= two.position.y && two.position.y + two.scale.y / 3 >= one.position.y;
  // TODO y doesn't seem to work properly (caused by the entity scale?)
  if (two.name == "enemy" && isCollidingX && false)
  {
    std::cout << two.name << isCollidingY << "\r\n";
    std::cout << "ballY: " << one.position.y << "\r\n";
    std::cout << "ballS: " << one.position.y + one.scale.y / 3 << "\r\n";
    std::cout << "enemyY: " << two.position.y << "\r\n";
    std::cout << "enemyS: " << two.position.y + two.scale.y / 3 << "\r\n";
  }
  return isCollidingX && isCollidingY;
}

#endif