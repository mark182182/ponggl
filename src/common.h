#ifndef COMMON_H
#define COMMON_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char *WINDOW_NAME = "PongGL";
GLFWwindow *window;
int WINDOW_HEIGHT = 720;
int WINDOW_WIDTH = 1280;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

#endif