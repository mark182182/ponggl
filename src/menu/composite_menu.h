#ifndef COMPOSITE_MENU_H
#define COMPOSITE_MENU_H

#include <GLFW/glfw3.h>
#include "../common.h"
#include "../shaders/shader.h"
#include "../entities/selector.h"
#include "../input.h"
#include "../text/text.h"

class CompositeMenu
{
public:
  Shader defaultShader;
  Shader textShader;
  Selector selector;
  std::vector<Text> selections;
  CompositeMenu(){};
  CompositeMenu(Shader &_defaultShader, Shader &_textShader)
  {
    defaultShader = _defaultShader;
    textShader = _textShader;
    Texture selectorTexture = Texture("textures/selector.png", GL_RGBA, GL_REPEAT);
    selector = Selector("selector", defaultShader, inputScale, inputPos, selectorTexture);
  };
  ~CompositeMenu(){};
  void add_text(Text text){};
  void move_selector(Text &text){};

protected:
  void init(){};
  void render(){};
};

#endif