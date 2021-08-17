#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "menu.h"

class MainMenu : public Menu
{
  using Menu::Menu;

public:
  void menu_controls()
  {
    move_selector_up_down();
    int e_key = glfwGetKey(window, GLFW_KEY_E);
    if (e_key == GLFW_PRESS && !is_e_pressed)
    {
      is_e_pressed = true;
      switch (currentSelectorPos)
      {
      case 0:
        audio.playSfx("audio/click.mp3");
        currentSelection = currentSelectorPos;
        GameState::set_state(State::GAMEPLAY);
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
        GameState::set_state(State::EXIT);
        break;
      default:
        GameState::set_state(State::EXIT);
      }
    }
    if (e_key == GLFW_RELEASE)
    {
      is_e_pressed = false;
    }
  };
  void set_menu_texts()
  {
    Text playText = Text("PLAY", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3 + Text::charHeight).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    add_text(playText);

    Text optionsText = Text("OPTIONS", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3 + Text::charHeight * 2).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    add_text(optionsText);

    Text controlsText = Text("CONTROLS", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3 + Text::charHeight * 3).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    add_text(controlsText);

    Text exitText = Text("EXIT", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3 + Text::charHeight * 4).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    add_text(exitText);
  }
};

#endif