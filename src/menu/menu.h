#ifndef MENU_H
#define MENU_H

#include <GLFW/glfw3.h>
#include "../common.h"
#include "../shaders/shader.h"
#include "../entities/selector.h"
#include "../text.h"

class Menu
{

public:
  Shader defaultShader;
  Shader textShader;
  Selector selector;

  Audio audio;

  std::vector<Text> selections;
  std::vector<Text> displayTexts;
  int currentSelectorPos = 0;
  int currentSelection = -1;

  bool is_w_pressed = false;
  bool is_s_pressed = false;
  bool is_e_pressed = false;

  Menu(){};
  Menu(Shader &_defaultShader, Shader &_textShader, Audio &_audio)
  {
    defaultShader = _defaultShader;
    textShader = _textShader;
    Texture selectorTexture = Texture("textures/selector.png", GL_RGBA, GL_CLAMP_TO_EDGE);
    selector = Selector("selector", defaultShader, inputScale, inputPos, selectorTexture);
    audio = _audio;
  };

  void init()
  {
    currentSelectorPos = 0;
    currentSelection = -1;
  }

  void add_text(Text text)
  {
    this->selections.push_back(text);
  }

  void add_display_text(Text text)
  {
    this->displayTexts.push_back(text);
  }

  void move_selector(Text &text)
  {
    selectorInputPos = glm::vec2(text.x - 4.0f, text.y - 10.0f);
    selectorInputScale = glm::vec2(text.width, text.charHeight * 2 + 30.0f);
  }

  void move_selector_up_down()
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
  }

  void render()
  {
    for (size_t i = 0; i < displayTexts.size(); i++)
    {
      displayTexts[i].render_text();
    }
    for (size_t i = 0; i < selections.size(); i++)
    {
      selections[i].render_text();
    }
    if (GameState::state == State::INIT)
    {
      move_selector(selections[0]);
    }
    else
    {
      move_selector(selections[currentSelectorPos]);
    }
    selector.handle_logic();
  };

protected:
  void menu_controls();
  void set_menu_texts();
};

#endif