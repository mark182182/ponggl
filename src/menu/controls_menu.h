#ifndef CONTROLS_MENU_H
#define CONTROLS_MENU_H

#include "menu.h"

class ControlsMenu : public Menu
{
  using Menu::Menu;

  bool is_w_pressed = false;
  bool is_s_pressed = false;
  bool is_e_released = false;

public:
  MainMenu *parentMenu;

  void set_parent_menu(MainMenu *_menu)
  {
    parentMenu = _menu;
  }

  void menu_controls()
  {
    int e_key = glfwGetKey(window, GLFW_KEY_E);
    std::cout << currentSelectorPos << "\n";
    if (e_key == GLFW_PRESS && is_e_released)
    {
      is_e_released = false;
      switch (currentSelectorPos)
      {
      case 0:
        audio.playSfx("audio/click.mp3");
        currentSelection = currentSelectorPos;
        parentMenu->init();
        break;
      }
    }
    if (e_key == GLFW_RELEASE)
    {
      is_e_released = true;
    }
  };
  void set_menu_texts()
  {
    Text up = Text("W: UP", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3 + Text::charHeight).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    Text down = Text("S: DOWN", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3 + Text::charHeight * 2).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    Text esc = Text("ESC: PAUSE", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3 + Text::charHeight * 3).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    Text exitText = Text("BACK", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3 + Text::charHeight * 4);
    exitText.set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    add_text(exitText);
    add_display_text(up);
    add_display_text(down);
    add_display_text(esc);
  }
};

#endif