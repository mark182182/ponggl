#ifndef MENU_H
#define MENU_H

#include <GLFW/glfw3.h>
#include "common.h"
#include "text.h"
#include "input.h"
#include "shaders/shader.h"
#include "entities/selector.h"

class Menu
{
  std::vector<Text> texts;

  Selector selector;

public:
  Shader defaultShader;
  Shader textShader;

  Menu(){};
  Menu(Shader &_defaultShader, Shader &_textShader)
  {
    defaultShader = _defaultShader;
    textShader = _textShader;
    Texture selectorTexture = Texture("textures/selector.png", GL_RGBA, GL_REPEAT);
    selector = Selector("selector", defaultShader, inputScale, inputPos, selectorTexture);
  };
  ~Menu(){};

  void add_text(Text text)
  {
    this->texts.push_back(text);
  }

  void init()
  {

    if (Input::selections.empty())
    {
      for (size_t i = 0; i < texts.size(); i++)
      {
        Input::add_to_selection(texts[i]);
      }
    };
  };

  void render()
  {
    for (size_t i = 0; i < texts.size(); i++)
    {
      texts[i].render_text();
    }
    if (GameState::is_state_changed() || GameState::state == State::INIT)
    {
      Input::move_selector(texts[0]);
    }
    selector.handle_logic();
  };
};

#endif