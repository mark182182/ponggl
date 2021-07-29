#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity
{
  using Entity::Entity;

public:
  float speed = 400.0f;
  void handle_logic()
  {
    position.y += deltaTime * inputPos.y * speed;
    shader.set_uniform_matrix4_value("model", 1, model);
    shader.set_uniform_matrix4_value("projection", 1, projection);
    shader.set_float_3("textColor", glm::vec3(1.0f, 1.0f, 1.0f));
    texture.activiate_and_bind(GL_TEXTURE0);
    bind();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position));
    model = glm::scale(model, glm::vec3(scale.x, scale.y, 0.0f));
    draw();
    update_position(position);
    unbind();
    shader.set_uniform_matrix4_value("model", 1, model);
  };
};

#endif