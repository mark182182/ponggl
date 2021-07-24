#ifndef BALL_H
#define BALL_H

#include "entity.h"
#include "../shaders/shader.h"
#include "../projection.h"
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>

class Ball : public Entity
{
  using Entity::Entity;

public:
  void handle_logic(float deltaTime, Player player, Enemy enemy, float xDir, float yDir, float prevPositionX, float prevPositionY)
  {

    if (check_collision(*this, player))
    {
      if (prevPositionX - position.x > 0)
      {
        xDir = -1 * deltaTime;
      }
      else
      {
        std::cout << "pos: " << prevPositionX - position.x << "\r\n";
        xDir = deltaTime;
      }
    }
    else if (check_collision(*this, enemy))
    {
      if (prevPositionX - position.x > 0)
      {
        xDir = deltaTime;
      }
      else
      {
        xDir = -1 * deltaTime;
      }
    }

    if (std::round(position.y) > WINDOW_HEIGHT - scale.y / 4 && std::round(position.y) < WINDOW_HEIGHT)
    {
      yDir = -1 * deltaTime;
    }
    else if (std::round(position.y) < scale.y / 4 && std::round(position.y) > 0)
    {
      yDir = 1 * deltaTime;
    }

    position.x = position.x + xDir;
    position.y = position.y + yDir;

    shader.set_uniform_matrix4_value("model", 1, model);
    shader.set_uniform_matrix4_value("projection", 1, projection);
    shader.set_float_3("textColor", glm::vec3(1.0f, 1.0f, 1.0f));
    bind();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
    model = glm::scale(model, glm::vec3(scale.x, scale.y, 0.0f));
    draw();
    unbind();
    shader.set_uniform_matrix4_value("model", 1, model);
    prevPositionX = position.x;
    prevPositionY = position.y;
  };
};

#endif