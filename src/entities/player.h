#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "../shaders/shader.h"
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>

class Player : public Entity
{
  using Entity::Entity;

public:
  float speed = 0.8f;
  void handle_logic()
  {
    shader.set_uniform_matrix4_value("projection", 1, projection);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(inputPos, 0.0f));
    model = glm::scale(model, glm::vec3(scale.x, scale.y, 0.0f));

    shader.set_uniform_matrix4_value("model", 1, model);
    shader.set_float_3("textColor", glm::vec3(1.0f, 1.0f, 1.0f));
    texture.activiate_and_bind(GL_TEXTURE0);
    
    bind();
    update_position(inputPos);
    draw();
    unbind();
  };
};

#endif