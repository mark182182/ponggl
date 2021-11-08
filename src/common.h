#ifndef COMMON_H
#define COMMON_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

const char *WINDOW_NAME = "PongGL";
GLFWwindow *window;
glm::mat4 projection;
int WINDOW_HEIGHT = 720;
int WINDOW_WIDTH = 1280;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool is_paused = false;

glm::vec2 inputPos = glm::vec2(0.0f, 0.0f);
glm::vec2 inputScale = glm::vec2(1.0f, 1.0f);

glm::vec2 selectorInputPos = glm::vec2(0.0f, 0.0f);
glm::vec2 selectorInputScale = glm::vec2(1.0f, 1.0f);

void calculate_delta_time()
{
  double currentFrame = glfwGetTime();
  deltaTime = !is_paused ? (currentFrame - lastFrame) : 0;
  lastFrame = currentFrame;
};

double lastTime = glfwGetTime();
double frameTime = 0.0f;
int frametimeFrames = 0;
int frameCounter = 0;

float get_frametime()
{
  double currentTime = glfwGetTime();
  frameCounter++;
  if (currentTime - lastTime >= 1.0)
  {
    frameTime = 1000.0f / double(frameCounter);
    frametimeFrames = frameCounter;
    frameCounter = 0;
    lastTime += 1.0f;
  }
  return frameTime;
};

#endif