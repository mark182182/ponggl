#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include "projection.h"
#include "entities/player.h"

class Input
{
  bool wireframe_mode;
  bool tab_pressed;
  float newPos;

  GLFWwindow *window;
  Player player;

public:
  Input(){};
  ~Input(){};
  Input(GLFWwindow *_window, Player &_player)
  {
    window = _window;
    player = _player;
  };
  void process_Input()
  {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);

    int tab_press = glfwGetKey(window, GLFW_KEY_TAB);

    if (tab_press == GLFW_PRESS && tab_pressed != true)
    {
      tab_pressed = true;
      wireframe_mode = !wireframe_mode;
      if (wireframe_mode)
      {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      }
      else
      {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      }
    }
    if (tab_press == GLFW_RELEASE)
    {
      tab_pressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
      newPos = inputPos.y - 10.0f * player.speed;
      if (newPos > 0)
      {
        inputPos.y = newPos;
      }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
      newPos = inputPos.y + 10.0f * player.speed;
      if (newPos < WINDOW_HEIGHT - player.scale.y / 2.5)
      {
        inputPos.y = newPos;
      }
    }
  };
};

#endif