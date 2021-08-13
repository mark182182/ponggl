#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H

#include "menu.h"

enum Resolution
{
  _800x600,
  _1280x720,
  _1920x1080
};

enum WindowTypes
{
  WINDOWED,
  FULLSCREEN,
  BORDERLESS_FULLSCREEN
};

class OptionsMenu : public Menu
{
  using Menu::Menu;

  bool is_a_pressed = false;
  bool is_d_pressed = false;
  bool is_e_released = false;

  int currentResolution = 2;
  int currentDifficulity = 1;
  int currentWindowType = 1;

public:
  MainMenu *parentMenu;

  void set_parent_menu(MainMenu *_menu)
  {
    parentMenu = _menu;
  }

  void menu_controls()
  {
    move_selector_up_down();
    int a_key = glfwGetKey(window, GLFW_KEY_A);
    int d_key = glfwGetKey(window, GLFW_KEY_D);
    if (a_key == GLFW_PRESS && !is_a_pressed)
    {
      is_a_pressed = true;
      if (currentSelectorPos == 0)
      {
        if (currentResolution > 1)
        {
          currentResolution--;
          move_selector_left(currentResolution, res_text());
        }
      }
      else if (currentSelectorPos == 1)
      {
        if (currentDifficulity > 1)
        {
          currentDifficulity--;
          move_selector_left(currentDifficulity, difficulity_text());
        }
      }
      else if (currentSelectorPos == 2)
      {
        if (currentWindowType > 1)
        {
          currentWindowType--;
          move_selector_left(currentWindowType, window_type_text());
        }
      }
    }
    if (a_key == GLFW_RELEASE)
    {
      is_a_pressed = false;
    }
    if (d_key == GLFW_PRESS && !is_d_pressed)
    {
      is_d_pressed = true;
      if (currentSelectorPos == 0)
      {
        if (currentResolution < sizeof(Resolution) - 1)
        {
          currentResolution++;
          move_selector_right(currentResolution, res_text());
        }
      }
      else if (currentSelectorPos == 1)
      {
        if (currentDifficulity < sizeof(Difficulity) - 1)
        {
          currentDifficulity++;
          move_selector_right(currentDifficulity, difficulity_text());
        }
      }
      else if (currentSelectorPos == 2)
      {
        if (currentWindowType < sizeof(WindowTypes) - 1)
        {
          currentWindowType++;
          move_selector_right(currentWindowType, window_type_text());
        }
      }
    }
    if (d_key == GLFW_RELEASE)
    {
      is_d_pressed = false;
    }
    int e_key = glfwGetKey(window, GLFW_KEY_E);
    if (e_key == GLFW_PRESS && is_e_released)
    {
      is_e_released = false;
      if (currentSelectorPos == 3)
      {
        audio.playSfx("audio/click.mp3");
        std::string res = current_resolution();
        std::string _widthStr = res.substr(0, res.find('x'));
        std::string _heightStr = res.substr(res.find('x') + 1, res.length());
        int _width = std::stoi(_widthStr);
        int _height = std::stoi(_heightStr);
        glfwSetWindowSize(window, _width, _height);
        const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        if (currentWindowType == 1)
        {
          glfwSetWindowMonitor(window, NULL, 0, 0, _width, _height, mode->refreshRate);
        }
        else if (currentWindowType == 2)
        {
          glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, _width, _height, mode->refreshRate);
        }
        else if (currentWindowType == 3)
        {
          glfwWindowHint(GLFW_RED_BITS, mode->redBits);
          glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
          glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
          glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

          glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
        }

        if (currentDifficulity == 1)
        {
          GameState::set_difficulity(Difficulity::EASY);
        }
        else if (currentDifficulity == 2)
        {
          GameState::set_difficulity(Difficulity::MEDIUM);
        }
        else if (currentDifficulity == 3)
        {
          GameState::set_difficulity(Difficulity::HARD);
        }
      }
      if (currentSelectorPos == 4)
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
    Text resolutionInfo = Text("RESOLUTION: ", WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0.3 + Text::charHeight).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    Text resolutionSettings = Text(res_text(), WINDOW_WIDTH * 0.6, WINDOW_HEIGHT * 0.3 + Text::charHeight).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

    Text difficulityInfo = Text("DIFFICULITY: ", WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0.3 + Text::charHeight * 2).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    Text difficulitySettings = Text(difficulity_text(), WINDOW_WIDTH * 0.6, WINDOW_HEIGHT * 0.3 + Text::charHeight * 2).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

    Text windowInfo = Text("WINDOW: ", WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0.3 + Text::charHeight * 3).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    Text windowSettings = Text(window_type_text(), WINDOW_WIDTH * 0.6, WINDOW_HEIGHT * 0.3 + Text::charHeight * 3).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

    Text apply = Text("APPLY", WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.3 + Text::charHeight * 4).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    Text exit = Text("BACK", WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.3 + Text::charHeight * 5).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

    add_text(resolutionSettings);
    add_text(difficulitySettings);
    add_text(windowSettings);
    add_text(apply);
    add_text(exit);
    add_display_text(resolutionInfo);
    add_display_text(difficulityInfo);
    add_display_text(windowInfo);
  }
  std::string current_resolution()
  {
    switch (currentResolution)
    {
    case 1:
      return "800x600";
    case 2:
      return "1280x720";
    case 3:
      return "1920x1080";
    default:
      return "1280x720";
    }
  }
  std::string current_difficulity()
  {
    switch (currentDifficulity)
    {
    case 1:
      return "EASY";
    case 2:
      return "MEDIUM";
    case 3:
      return "HARD";
    default:
      return "EASY";
    }
  }
  std::string current_window_type()
  {
    switch (currentWindowType)
    {
    case 1:
      return "WINDOWED";
    case 2:
      return "FULLSCREEN";
    case 3:
      return "BORDERLESS";
    default:
      return "WINDOWED";
    }
  }

  std::string res_text()
  {
    return "< " + current_resolution() + " >";
  }

  std::string difficulity_text()
  {
    return "< " + current_difficulity() + " >";
  }

  std::string window_type_text()
  {
    return "< " + current_window_type() + " >";
  }

  void move_selector_right(int &_option, std::string _text)
  {

    selections[currentSelectorPos].set_text(_text);
    selections[currentSelectorPos].render_text();
  }

  void move_selector_left(int &_option, std::string _text)
  {
    selections[currentSelectorPos].set_text(_text);
    selections[currentSelectorPos].render_text();
  }
};

#endif