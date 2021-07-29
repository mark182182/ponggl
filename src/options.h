#ifndef OPTIONS_H
#define OPTIONS_H

#include <GLFW/glfw3.h>
#include "common.h"

class Options
{

  void resize_window(int height, int width)
  {
    glfwSetWindowSize(window, height, width);
    WINDOW_HEIGHT = height;
    WINDOW_WIDTH = width;
  }

  void maximize_window()
  {
    glfwMaximizeWindow(window);
  };
};

#endif