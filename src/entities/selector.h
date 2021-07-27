#ifndef MENU_H
#define MENU_H

#include <GLFW/glfw3.h>
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

class Selector : public Entity
{

  using Entity::Entity;

public:
  void handle_logic()
  {
    float timeBasedValue = glm::sin(glfwGetTime() * 4);
    shader.use();
    shader.set_uniform_matrix4_value("projection", 1, projection);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(inputPos, 0.0f));
    model = glm::scale(model, glm::vec3(inputScale, 0.0f));

    shader.set_uniform_matrix4_value("model", 1, model);
    shader.set_float_3("textColor", glm::vec3(timeBasedValue, timeBasedValue, timeBasedValue));
    texture.activiate_and_bind(GL_TEXTURE0);

    bind();
    update_position(inputPos);
    update_scale(inputScale);
    draw();
    unbind();
  };
};

#endif