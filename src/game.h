#ifndef GAME_H
#define GAME_H

#include "entities/entity.h"
#include "entities/player.h"
#include "entities/enemy.h"
#include "entities/ball.h"
#include "audio.h"
#include "input.h"
#include <GLFW/glfw3.h>
#include <iostream>

enum State
{
  MENU,
  GAMEPLAY,
  EXIT
};

class Game
{
  State state;
  GLFWwindow *window = NULL;
  Audio audio = Audio();
  float xDirection = -1;
  float yDirection = 0;
  float prevPositionX;
  float prevPositionY;
  float deltaTime;

public:
  Player player;
  Enemy enemy;
  Ball ball;
  Input input;

  int playerScore = 0;
  int enemyScore = 0;
  Game(){};
  Game(GLFWwindow *_window)
  {
    window = _window;
  }
  ~Game(){};

  void set_state(State _state)
  {
    state = _state;
  }

  void set_delta_time(float &_deltaTime)
  {
    deltaTime = _deltaTime;
  }

  void set_prev_position_x(float &_prevPositionX)
  {
    prevPositionX = _prevPositionX;
  }

  void set_prev_position_y(float &_prevPositionY)
  {
    prevPositionX = _prevPositionY;
  }

  void init_entities()
  {
    Shader defaultShader = Shader("shaders/vertex.vs", "shaders/fragment.fs");
    Shader enemyShader = Shader("shaders/vertex.vs", "shaders/fragment.fs");
    Shader ballShader = Shader("shaders/vertex.vs", "shaders/fragment.fs");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f);

    player = Player("player", defaultShader, projection, glm::vec2(WINDOW_WIDTH / 8, WINDOW_WIDTH / 4), inputPos);
    enemy = Enemy("enemy", enemyShader, projection, glm::vec2(WINDOW_WIDTH / 8, WINDOW_WIDTH / 4), glm::vec2(WINDOW_WIDTH * 0.8, WINDOW_HEIGHT * 0.5));
    ball = Ball("ball", ballShader, projection, glm::vec2(WINDOW_WIDTH / 8, WINDOW_WIDTH / 16), glm::vec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5));
    ball.set_audio(audio);

    xDirection = -1;
    yDirection = 0;
    inputPos.y = WINDOW_HEIGHT * 0.5;
  }

  void update_game_logic()
  {
    // There should be a better way to update the input
    Input(window, player).process_Input();
    switch (state)
    {
    case MENU:
      // TODO implement menu
      break;
    case GAMEPLAY:
      handle_gameplay_logic();
      break;
    case EXIT:
      exit_game();
      break;
    default:
      exit_game();
    }
  };

private:
  void handle_gameplay_logic()
  {
    prevPositionX = glm::normalize(glm::vec3(ball.position.x, ball.position.y, 0.0f)).x;
    prevPositionY = glm::normalize(glm::vec3(ball.position.x, ball.position.y, 0.0f)).y;

    player.handle_logic();
    enemy.handle_logic(ball);
    ball.handle_logic(deltaTime, player, enemy, xDirection, yDirection, prevPositionX, prevPositionY);

    if (ball.position.x <= WINDOW_WIDTH && ball.position.x >= WINDOW_WIDTH * 0.8 + enemy.scale.x / 4)
    {
      init_entities();
      playerScore++;
    }

    if (ball.position.x >= 0 && ball.position.x <= WINDOW_WIDTH * 0.2 - player.scale.x / 4)
    {
      init_entities();
      enemyScore++;
    }
  }

  void exit_game()
  {
    glfwSetWindowShouldClose(window, true);
  }
};

#endif