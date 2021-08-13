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
    if (e_key == GLFW_PRESS && is_e_released)
    {
      is_e_released = false;
      if (currentSelectorPos == 0)
      {
        audio.playSfx("audio/click.mp3");
        currentSelection = currentSelectorPos;
        parentMenu->init();
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
    Text prev = Text("A: PREVIOUS OPTION", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3 + Text::charHeight * 2).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    Text down = Text("S: DOWN", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3 + Text::charHeight * 3).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    Text next = Text("D: NEXT OPTION", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3 + Text::charHeight * 4).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    Text tab = Text("TAB: WIREFRAME MODE", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3 + Text::charHeight * 5).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    Text esc = Text("ESC: PAUSE", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3 + Text::charHeight * 6).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    Text exitText = Text("BACK", WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.3 + Text::charHeight * 8).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    add_text(exitText);
    add_display_text(up);
    add_display_text(prev);
    add_display_text(down);
    add_display_text(next);
    add_display_text(tab);
    add_display_text(esc);
  }
};

#endif