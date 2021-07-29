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
  Text optionsText;
  Text controlsText;
  Text exitText;

public:
  Text playText;

  Shader defaultShader;
  Shader textShader;

  Menu(){};
  Menu(Shader &_defaultShader, Shader &_textShader)
  {
    defaultShader = _defaultShader;
    textShader = _textShader;
    playText = Text(textShader, "PLAY", WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    optionsText = Text(textShader, "OPTIONS", WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5 + playText.charHeight, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    // TODO WEIRD BLACK, doesn't show up
    controlsText = Text(textShader, "CONTROLS", WINDOW_WIDTH * 0.5, optionsText.y + optionsText.charHeight, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    exitText = Text(textShader, "EXIT", WINDOW_WIDTH * 0.5, controlsText.y + controlsText.charHeight, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
  };
  ~Menu(){};

  void init()
  {

    if (Input::selections.empty())
    {
      Input::add_to_selection(exitText);
      Input::add_to_selection(controlsText);
      Input::add_to_selection(optionsText);
      Input::add_to_selection(playText);
    };
  };

  void render()
  {
    if (GameState::is_state_changed() || GameState::state == State::INIT)
    {
      Input::move_selector(playText);
    }
    // std::cout << defaultShader.ID << "\r\n";
    playText.render_text();
    optionsText.render_text();
    controlsText.render_text();
    exitText.render_text();
    Texture selectorTexture = Texture("textures/selector.png", GL_RGBA, GL_REPEAT);
    Selector("selector", defaultShader, projection, inputScale, inputPos, selectorTexture).handle_logic();
  };
};

#endif