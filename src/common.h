#ifndef COMMON_H
#define COMMON_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char *WINDOW_NAME = "PongGL";
GLFWwindow *window;
int WINDOW_HEIGHT = 720;
int WINDOW_WIDTH = 1280;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void setDeltaTime(float offset)
{
  float currentFrame = glfwGetTime();
  deltaTime = (currentFrame - lastFrame) * offset;
  lastFrame = currentFrame;
}

#endif