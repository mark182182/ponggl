#ifndef GAME_STATE_H
#define GAME_STATE_H

enum State
{
  MENU,
  GAMEPLAY,
  EXIT,
  INIT
};

enum Difficulity
{
  EASY,
  MEDIUM,
  HARD
};

class GameState
{

public:
  inline static State state = INIT;
  inline static Difficulity difficulity = EASY;
  inline static State prevState;

  static void set_state(State _state)
  {
    GameState::prevState = state;
    GameState::state = _state;
  }

  static bool is_state_changed()
  {
    bool isChanged = GameState::prevState != GameState::state;
    GameState::prevState = state;
    return isChanged;
  }

  static void set_difficulity(Difficulity _difficulity)
  {
    GameState::difficulity = _difficulity;
  }
};

#endif