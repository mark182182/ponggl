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
    shader.set_float_3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.set_float_3("lightColor", lightColor);
    shader.set_float_3("lightPos", lightPos);
    texture.activiate_and_bind(GL_TEXTURE0);
    bind();
    update_position(position);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position));
    model = glm::scale(model, glm::vec3(scale.x, scale.y, 0.0f));
    draw();
    unbind();
    shader.set_uniform_matrix4_value("model", 1, model);
  };
};

#endif