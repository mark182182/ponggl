#ifndef SUBMENU_H
#define SUBMENU_H

#include "menu.h"

class Submenu : public Menu
{
  using Menu::Menu;

public:
  void log()
  {
    std::cout << "compMenu here"
              << "\n";
  };
};

#endif
