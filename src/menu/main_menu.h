#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "menu.h"

class MainMenu : public Menu
{
  using Menu::Menu;

  bool is_w_pressed = false;
  bool is_s_pressed = false;

public:
  void menu_controls()
  {
    int w_key = glfwGetKey(window, GLFW_KEY_W);
    int s_key = glfwGetKey(window, GLFW_KEY_S);
    if (w_key == GLFW_PRESS && !is_w_pressed)
    {
      is_w_pressed = true;
      if (currentSelectorPos > 0)
      {
        currentSelectorPos--;
      }
    }
    if (w_key == GLFW_RELEASE)
    {
      is_w_pressed = false;
    }
    if (s_key == GLFW_PRESS && !is_s_pressed)
    {
      is_s_pressed = true;
      if (currentSelectorPos < selections.size() - 1)
      {
        currentSelectorPos++;
      }
    }
    if (s_key == GLFW_RELEASE)
    {
      is_s_pressed = false;
    }
    int e_key = glfwGetKey(window, GLFW_KEY_E);
    if (e_key == GLFW_PRESS && !is_e_pressed)
    {
      is_e_pressed = true;
      switch (currentSelectorPos)
      {
      case 0:
        audio.playSfx("audio/click.mp3");
        currentSelection = currentSelectorPos;
        GameState::set_state(GAMEPLAY);
        break;
      case 1:
        currentSelection = currentSelectorPos;
        audio.playSfx("audio/click.mp3");
        break;
      case 2:
        currentSelection = currentSelectorPos;
        audio.playSfx("audio/click.mp3");
        break;
      case 3:
        GameState::set_state(EXIT);
        break;
      default:
        GameState::set_state(EXIT);
      }
    }
    if (e_key == GLFW_RELEASE)
    {
      is_e_pressed = false;
    }
  };
  void set_menu_texts()
  {
    Text playText = Text("PLAY", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3 + Text::charHeight);
    playText.set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    add_text(playText);

    Text optionsText = Text("OPTIONS", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3 + Text::charHeight * 2);
    optionsText.set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    add_text(optionsText);

    Text controlsText = Text("CONTROLS", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3 + Text::charHeight * 3);
    controlsText.set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    add_text(controlsText);

    Text exitText = Text("EXIT", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3 + Text::charHeight * 4);
    exitText.set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    add_text(exitText);
  }
};

#endif