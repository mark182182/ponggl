#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <vector>
#include "projection.h"
#include "entities/player.h"
#include "game_state.h"

class Input
{
  float newPos;

  GLFWwindow *window;
  Player player;

  bool wireframe_mode = false;
  bool tab_pressed = false;
  bool w_pressed = false;
  bool s_pressed = false;

public:
  std::vector<Text> selections;
  int currentSelection = 0;

  Input(){};
  ~Input(){};
  Input(GLFWwindow *_window, Player &_player)
  {
    window = _window;
    player = _player;
  };
  void process_Input()
  {
    switch (GameState::state)
    {
    case MENU:
      menu_controls();
      break;
    case GAMEPLAY:
      gameplay_controls();
      break;
    default:
      menu_controls();
    };
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
  };

  void move_selector(Text &text)
  {
    inputPos = glm::vec2(text.x - text.width - 10.0f, text.y - text.charHeight - 10.0f);
    inputScale = glm::vec2(text.x + 40.0f, text.charHeight * 2 + 30.0f);
  }

  void add_to_selection(Text &text)
  {
    this->selections.push_back(text);
  }

private:
  void menu_controls()
  {
    // TODO fix this
    int w_press = glfwGetKey(window, GLFW_KEY_W);
    int s_press = glfwGetKey(window, GLFW_KEY_TAB);
    if (w_press == GLFW_PRESS && !w_pressed)
    {
      w_pressed = true;
      if (currentSelection < selections.size())
      {
        currentSelection++;
        move_selector(selections[currentSelection]);
      }
    }
    if (s_press == GLFW_PRESS && !s_pressed)
    {
      s_pressed = true;
      if (currentSelection > 0)
      {
        currentSelection--;
        move_selector(selections[currentSelection]);
      }
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
      // TODO
    }
    if (w_press == GLFW_RELEASE)
    {
      w_pressed = false;
    }
    if (s_press == GLFW_RELEASE)
    {
      std::cout << s_pressed << "\r\n";
      s_pressed = false;
    }
  };
  void gameplay_controls()
  {
    int tab_press = glfwGetKey(window, GLFW_KEY_TAB);

    if (tab_press == GLFW_PRESS && !tab_pressed)
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