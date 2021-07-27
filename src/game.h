#ifndef GAME_H
#define GAME_H

#include "entities/entity.h"
#include "entities/player.h"
#include "entities/enemy.h"
#include "entities/ball.h"
#include "entities/selector.h"
#include "game_state.h"
#include "audio.h"
#include "input.h"
#include <GLFW/glfw3.h>
#include <iostream>

class Game
{
  GLFWwindow *window = NULL;
  Audio audio = Audio();
  float xDirection = 0;
  float yDirection = 0;
  float prevPositionX;
  float prevPositionY;
  float deltaTime;

  glm::mat4 projection;
  Shader defaultShader;

public:
  Player player;
  Enemy enemy;
  Ball ball;
  Selector selector;

  Input input;
  Shader textShader;
  Texture padTexture;

  int playerScore = 0;
  int enemyScore = 0;
  bool playerGoal = false;
  bool enemyGoal = false;

  Game(){};
  Game(GLFWwindow *_window)
  {
    window = _window;
  }
  ~Game(){};

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

  void init_shaders()
  {
    defaultShader = Shader("shaders/vertex.vs", "shaders/fragment.fs");
    textShader = Shader("shaders/text_vertex.vs", "shaders/text_fragment.fs");

    padTexture = Texture("textures/pad.png", GL_RGB, GL_REPEAT);

    projection = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f);
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
    player = Player("player", defaultShader, projection, glm::vec2(WINDOW_WIDTH / 10, WINDOW_HEIGHT / 1.5), inputPos, padTexture);
    enemy = Enemy("enemy", defaultShader, projection, glm::vec2(WINDOW_WIDTH / 10, WINDOW_HEIGHT / 1.5), glm::vec2(WINDOW_WIDTH * 0.8, WINDOW_HEIGHT * 0.5), padTexture);
    Texture ballTexture = Texture("textures/ball1.png", GL_RGBA, GL_REPEAT);
    ball = Ball("ball", defaultShader, projection, glm::vec2(WINDOW_WIDTH / 8, WINDOW_WIDTH / 16), glm::vec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5), ballTexture);
    ball.set_audio(audio);

    textShader.set_uniform_matrix4_value("projection", 1, projection);
    initText();

    xDirection = playerGoal ? 1.0f : -1.0f;
    yDirection = 0;
    inputPos.y = WINDOW_HEIGHT * 0.5;
  }

  void update_game_logic()
  {
    // There should be a better way to update the input
    Input input = Input(window, player);
    Text playText = Text(textShader, "PLAY", WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    Text optionsText = Text(textShader, "OPTIONS", WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5 + playText.charHeight, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    Text exitText = Text(textShader, "EXIT", WINDOW_WIDTH * 0.5, optionsText.y + optionsText.charHeight, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

    input.add_to_selection(exitText);
    input.add_to_selection(optionsText);
    input.add_to_selection(playText);

    Texture selectorTexture = Texture("textures/selector.png", GL_RGBA, GL_REPEAT);

    selector = Selector("selector", defaultShader, projection, inputScale, inputPos, selectorTexture);

    input.process_Input();
    switch (GameState::state)
    {
    case MENU:
      if (GameState::is_state_changed() || GameState::state == State::INIT)
      {
        input.move_selector(playText);
      }
      playText.render_text();
      optionsText.render_text();
      exitText.render_text();
      selector.handle_logic();
      break;
    case GAMEPLAY:
      Text(textShader, std::to_string(playerScore), 20.0f, 40.0f + Text::charHeight, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f)).render_text();
      Text(textShader, std::to_string(enemyScore), WINDOW_WIDTH * 0.90, 40.0f + Text::charHeight, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f)).render_text();
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
    prevPositionX = glm::normalize(glm::vec3(ball.position.x, ball.position.y, 0.0f)).x;
    prevPositionY = glm::normalize(glm::vec3(ball.position.x, ball.position.y, 0.0f)).y;

    player.handle_logic();
    enemy.handle_logic(ball);
    ball.handle_logic(deltaTime, player, enemy, xDirection, yDirection);

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