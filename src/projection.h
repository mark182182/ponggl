#ifndef PROJECTION_H
#define PROJECTION_H

#include "const.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::mat4 projection;
glm::vec2 inputPos = glm::vec2(WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0.5);
glm::vec2 inputScale = glm::vec2(1.0f, 1.0f);

#endif