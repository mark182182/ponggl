#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "menu.h"

class PauseMenu : public Menu
{
  using Menu::Menu;

  bool is_w_pressed = false;
  bool is_s_pressed = false;
  bool is_e_released = false;

public:
  void menu_controls()
  {
    move_selector_up_down();
    int e_key = glfwGetKey(window, GLFW_KEY_E);
    if (e_key == GLFW_PRESS && is_e_released)
    {
      is_e_released = false;
      if (currentSelectorPos == 0)
      {
        audio.playSfx("audio/click.mp3");
        currentSelection = currentSelectorPos;
        is_paused = false;
      }
      if (currentSelectorPos == 1)
      {
        audio.playSfx("audio/click.mp3");
        currentSelection = currentSelectorPos;
        is_paused = false;
        GameState::set_state(State::MENU);
      }
    }
    if (e_key == GLFW_RELEASE)
    {
      is_e_released = true;
    }
  };
  void set_menu_texts()
  {
    Text continueText = Text("CONTINUE", WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.3 + Text::charHeight).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    Text back = Text("BACK TO MAIN MENU", WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.3 + Text::charHeight * 2).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    add_text(continueText);
    add_text(back);
  }
};

#endif