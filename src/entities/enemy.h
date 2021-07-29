#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include "../shaders/shader.h"
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>

class Enemy : public Entity
{
  using Entity::Entity;

public:
  void handle_logic(Entity &e)
  {
    float newPos = position.y + (e.position.y - position.y) * deltaTime * speed;
    if (newPos < WINDOW_HEIGHT - scale.y / 2.5)
    {
      position.y = newPos;
    }
    shader.set_uniform_matrix4_value("model", 1, model);
    shader.set_uniform_matrix4_value("projection", 1, projection);
    shader.set_float_3("textColor", glm::vec3(1.0f, 1.0f, 1.0f));
    texture.activiate_and_bind(GL_TEXTURE0);
    bind();
    update_position(position);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
    model = glm::scale(model, glm::vec3(scale.x, scale.y, 0.0f));
    draw();
    unbind();
    shader.set_uniform_matrix4_value("model", 1, model);
  };
};

#endif