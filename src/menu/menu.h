#ifndef MENU_H
#define MENU_H

#include <GLFW/glfw3.h>
#include "../common.h"
#include "../shaders/shader.h"
#include "../entities/selector.h"
#include "../text/text.h"

class Menu
{

public:
  Shader defaultShader;
  Shader textShader;
  Selector selector;

  Audio audio;

  std::vector<Text> selections;
  int currentSelection = 0;

  Menu(){};
  Menu(Shader &_defaultShader, Shader &_textShader, Audio &_audio)
  {
    defaultShader = _defaultShader;
    textShader = _textShader;
    Texture selectorTexture = Texture("textures/selector.png", GL_RGBA, GL_REPEAT);
    selector = Selector("selector", defaultShader, inputScale, inputPos, selectorTexture);
    audio = _audio;
  };

  void add_text(Text text)
  {
    this->selections.push_back(text);
  }

  void move_selector(Text &text)
  {
    inputPos = glm::vec2(text.x - 4.0f, text.y - 10.0f);
    inputScale = glm::vec2(text.width, text.charHeight * 2 + 30.0f);
  }

  void render()
  {
    for (size_t i = 0; i < selections.size(); i++)
    {
      selections[i].render_text();
    }
    if (GameState::is_state_changed() || GameState::state == State::INIT)
    {
      move_selector(selections[0]);
    }
    else
    {
      move_selector(selections[currentSelection]);
    }
    selector.handle_logic();
  };

protected:
  void menu_controls();
  void set_menu_texts();
};

#endif