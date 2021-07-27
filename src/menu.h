#ifndef MENU_H
#define MENU_H

#include <GLFW/glfw3.h>
#include "const.h"

class Menu
{

  void resize_window(GLFWwindow *window, int height, int width)
  {
    glfwSetWindowSize(window, height, width);
    WINDOW_HEIGHT = height;
    WINDOW_WIDTH = width;
  }

  void maximize_window(GLFWwindow *window)
  {
    glfwMaximizeWindow(window);
  };
};

#endif