#ifndef MENU_TEXT_H
#define MENU_TEXT_H

#include "text.h"
#include "../menu/submenu.h"

class MenuText : public Text
{
  using Text::Text;

public:
  bool isSelected = false;
  Submenu submenu;
  void setIsSelected(bool _isSelected)
  {
    isSelected = _isSelected;
  }
  void setSubMenu(Submenu _submenu)
  {
    submenu = _submenu;
  }
};

#endif