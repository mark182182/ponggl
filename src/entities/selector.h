#ifndef SELECTOR_H
#define SELECTOR_H

#include "entity.h"

class Selector : public Entity
{
  using Entity::Entity;

public:
  void handle_logic()
  {
    float timeBasedValue = glm::sin(glfwGetTime() * 4);
    shader.use();
    shader.set_uniform_matrix4_value("model", 1, model);
    shader.set_uniform_matrix4_value("projection", 1, projection);
    shader.set_float_3("textColor", glm::vec3(timeBasedValue, timeBasedValue, timeBasedValue));
    texture.activiate_and_bind(GL_TEXTURE0);
    bind();
    update_position(selectorInputPos);
    update_scale(selectorInputScale);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(selectorInputPos, 0.0f));
    model = glm::scale(model, glm::vec3(selectorInputScale, 0.0f));

    draw();
    unbind();
    shader.set_uniform_matrix4_value("model", 1, model);
  };
};

#endif