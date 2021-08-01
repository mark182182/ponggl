#ifndef MENU_H
#define MENU_H

#include "../input.h"
#include "composite_menu.h"

class Menu : public CompositeMenu
{
  using CompositeMenu::CompositeMenu;

public:
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
      Input::selectionSize = selections.size();
      move_selector(selections[0]);
    }
    else
    {
      move_selector(selections[Input::currentSelection]);
    }
    selector.handle_logic();
  };
};

#endif