#ifndef GAME_H
#define GAME_H

#include "entities/entity.h"
#include "entities/player.h"
#include "entities/enemy.h"
#include "entities/ball.h"
#include "game_state.h"
#include "audio.h"
#include "input.h"
#include "menu.h"
#include <GLFW/glfw3.h>
#include <iostream>

class Game
{
  Audio audio = Audio();
  float xDirection = 0;
  float yDirection = 0;

  glm::mat4 projection;

  int playerScore = 0;
  int enemyScore = 0;
  bool playerGoal = false;
  bool enemyGoal = false;

public:
  Shader defaultShader;
  Shader textShader;

  Player player;
  Enemy enemy;
  Ball ball;

  Texture padTexture;

  Menu menu;

  Game(){};
  ~Game(){};

  void init_shaders()
  {
    defaultShader = Shader("shaders/vertex.vs", "shaders/fragment.fs");
    textShader = Shader("shaders/text_vertex.vs", "shaders/text_fragment.fs");

    padTexture = Texture("textures/pad.png", GL_RGBA, GL_REPEAT);

    projection = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f);

    menu = Menu(defaultShader, textShader);
    menu.init();
  }

  void init_shader_vars()
  {
    player.shader.use().set_int("image", 0);
    enemy.shader.use().set_int("image", 0);
    ball.shader.use().set_int("image", 0);
    textShader.use().set_int("image", 0);
  }

  void init_entities()
  {
    player = Player("player", defaultShader, projection, glm::vec2(WINDOW_WIDTH / 10, WINDOW_HEIGHT / 1.5), glm::vec2(WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0.5), padTexture);
    Input::init_input();

    enemy = Enemy("enemy", defaultShader, projection, glm::vec2(WINDOW_WIDTH / 10, WINDOW_HEIGHT / 1.5), glm::vec2(WINDOW_WIDTH * 0.8, WINDOW_HEIGHT * 0.5), padTexture);
    switch (GameState::difficulity)
    {
    EASY:
      enemy.speed = 1.5f;
      break;
    MEDIUM:
      enemy.speed = 2.0f;
      break;
    HARD:
      enemy.speed = 2.5f;
      break;
    default:
      enemy.speed = 1.5f;
    }
    Texture ballTexture = Texture("textures/ball1.png", GL_RGBA, GL_REPEAT);
    ball = Ball("ball", defaultShader, projection, glm::vec2(WINDOW_WIDTH / 8, WINDOW_WIDTH / 16), glm::vec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5), ballTexture);
    ball.set_audio(audio);

    textShader.set_uniform_matrix4_value("projection", 1, projection);
    initText();

    xDirection = playerGoal ? 1.0f : -1.0f;
    yDirection = 0;
  }

  void update_game_logic()
  {

    switch (GameState::state)
    {
    case MENU:
      // TODO fix the menu
      menu.render();
      break;
    case GAMEPLAY:
      if (GameState::is_state_changed())
      {
        inputPos.y = 0.0f;
        player.position.y = WINDOW_HEIGHT * 0.5;
      }
      Text(textShader, std::to_string(playerScore), 20.0f, 40.0f + Text::charHeight, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f))
          .render_text();
      Text(textShader, std::to_string(enemyScore), WINDOW_WIDTH * 0.95, 40.0f + Text::charHeight, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f)).render_text();
      Input::set_player(player);
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
    defaultShader.use();

    player.handle_logic();
    enemy.handle_logic(ball);
    ball.handle_logic(player, enemy, xDirection, yDirection);

    if (ball.position.x <= WINDOW_WIDTH && ball.position.x >= WINDOW_WIDTH * 0.8 + enemy.scale.x / 4)
    {
      playerGoal = true;
      enemyGoal = false;
      playerScore++;
      init_entities();
    }

    if (ball.position.x >= 0 && ball.position.x <= WINDOW_WIDTH * 0.2 - player.scale.x / 4)
    {
      playerGoal = false;
      enemyGoal = true;
      enemyScore++;
      init_entities();
    }
  }

  void exit_game()
  {
    glfwSetWindowShouldClose(window, true);
  }
};

#endif