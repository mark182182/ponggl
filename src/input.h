#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <vector>
#include "projection.h"
#include "entities/player.h"
#include "game_state.h"
#include "text/text.h"

Player player;
bool wireframe_mode;
bool tab_pressed;

class Input
{

public:
  inline static int currentSelection = 0;
  inline static int selectionSize = 0;
  inline static bool selectionSignal = false;

  inline static Audio audio;

  static void init_input()
  {
    wireframe_mode = false;
    glfwSetKeyCallback(window, process_input);
  };

  static void set_player(Player &_player)
  {
    player = _player;
  }

  static void process_input(GLFWwindow *_window, int key, int scancode, int action, int mods)
  {
    switch (GameState::state)
    {
    case MENU | INIT:
      menu_controls(key, action);
      break;
    case GAMEPLAY:
      gameplay_controls(key, action);
      break;
    default:
      menu_controls(key, action);
    };
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(_window, true);
  };

  static void menu_controls(int &key, int &action)
  {
    bool is_w_press = key == GLFW_KEY_W;
    bool is_s_press = key == GLFW_KEY_S;
    if (is_w_press && action == GLFW_PRESS)
    {
      if (currentSelection > 0)
      {
        currentSelection--;
      }
    }
    if (is_s_press && action == GLFW_PRESS)
    {
      if (Input::currentSelection < selectionSize - 1)
      {
        currentSelection++;
      }
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
      // TODO
      switch (currentSelection)
      {
      case 0:
        audio.playSfx("audio/click.mp3");
        GameState::set_state(GAMEPLAY);
        break;
      case 1:
        audio.playSfx("audio/click.mp3");
        send_singnal();
        break;
      case 2:
        audio.playSfx("audio/click.mp3");
        send_singnal();
        break;
      case 3:
        GameState::set_state(EXIT);
        break;
      default:
        GameState::set_state(EXIT);
      }
    }
  };

  static void gameplay_controls(int &key, int &action)
  {
    bool is_tab_press = key == GLFW_KEY_TAB;
    if (is_tab_press && action == GLFW_PRESS)
    {
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

    bool is_w_press = key == GLFW_KEY_W;
    bool is_s_press = key == GLFW_KEY_S;
    if (is_w_press && action == GLFW_PRESS || is_w_press && action == GLFW_REPEAT)
    {
      if (player.position.y > 0)
      {
        inputPos.y = -1;
      }
      else
      {
        inputPos.y = -0;
      }
    }
    if (is_s_press && action == GLFW_PRESS || is_s_press && action == GLFW_REPEAT)
    {
      if (player.position.y < WINDOW_HEIGHT - player.scale.y / 2.5)
      {
        inputPos.y = 1;
      }
      else
      {
        inputPos.y = 0;
      }
    }
    if (is_w_press && action == GLFW_RELEASE || is_s_press && action == GLFW_RELEASE)
    {
      inputPos.y = 0;
    }
  };

  static void send_singnal()
  {
    selectionSignal = !selectionSignal;
    selectionSignal = !selectionSignal;
  };
};

#endif