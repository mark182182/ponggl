#ifndef GAME_H
#define GAME_H

#include "entities/entity.h"
#include "entities/player.h"
#include "entities/enemy.h"
#include "entities/ball.h"
#include "game_state.h"
#include "audio.h"
#include "text.h"
#include "menu/main_menu.h"
#include "menu/controls_menu.h"
#include "menu/options_menu.h"
#include <GLFW/glfw3.h>
#include <iostream>

class Game
{
  Audio audio = Audio();
  float xDirection = 0;
  float yDirection = 0;

  int playerScore = 0;
  int enemyScore = 0;
  bool playerGoal = false;
  bool enemyGoal = false;

  bool is_wireframe_mode = false;
  bool is_tab_pressed = false;
  bool is_esc_pressed = false;

public:
  Shader defaultShader;
  Shader textShader;

  Player player;
  Enemy enemy;
  Ball ball;

  Texture padTexture;
  MainMenu mainMenu;
  OptionsMenu optionsMenu;
  ControlsMenu controlsMenu;

  Game(){};
  ~Game(){};

  void init_shaders()
  {
    defaultShader = Shader("shaders/vertex.vs", "shaders/fragment.fs");
    textShader = Shader("shaders/text_vertex.vs", "shaders/text_fragment.fs");
    initText();

    padTexture = Texture("textures/pad.png", GL_RGBA, GL_REPEAT);

    projection = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f);

    mainMenu = MainMenu(defaultShader, textShader, audio);
    mainMenu.set_menu_texts();

    optionsMenu = OptionsMenu(defaultShader, textShader, audio);
    optionsMenu.set_parent_menu(&mainMenu);
    optionsMenu.set_menu_texts();

    controlsMenu = ControlsMenu(defaultShader, textShader, audio);
    controlsMenu.set_parent_menu(&mainMenu);
    controlsMenu.set_menu_texts();
  }

  void init_shader_vars()
  {
    defaultShader.use().set_int("image", 0);
    player.shader.use().set_int("image", 0);
    enemy.shader.use().set_int("image", 0);
    ball.shader.use().set_int("image", 0);
    textShader.use().set_int("image", 0);
  }

  void init_entities()
  {
    player = Player("player", defaultShader, glm::vec2(WINDOW_WIDTH / 10, WINDOW_HEIGHT / 1.5), glm::vec2(WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0.5), padTexture);

    enemy = Enemy("enemy", defaultShader, glm::vec2(WINDOW_WIDTH / 10, WINDOW_HEIGHT / 1.5), glm::vec2(WINDOW_WIDTH * 0.8, WINDOW_HEIGHT * 0.5), padTexture);
    Texture ballTexture = Texture("textures/ball1.png", GL_RGBA, GL_REPEAT);

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
    ball = Ball("ball", defaultShader, glm::vec2(WINDOW_WIDTH / 8, WINDOW_WIDTH / 16), glm::vec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5), ballTexture);
    ball.set_audio(audio);

    textShader.set_uniform_matrix4_value("projection", 1, projection);

    xDirection = playerGoal ? 1.0f : -1.0f;
    yDirection = 0;
  }

  void update_game_logic()
  {
    switch (GameState::state)
    {
    case MENU:
      switch (mainMenu.currentSelection)
      {
      case 1:
        optionsMenu.menu_controls();
        optionsMenu.render();
        break;
      case 2:
        controlsMenu.menu_controls();
        controlsMenu.render();
        break;
      default:
        mainMenu.menu_controls();
        mainMenu.render();
      }
      break;
    case GAMEPLAY:
      if (GameState::is_state_changed())
      {
        inputPos.y = 0.0f;
        player.position.y = WINDOW_HEIGHT * 0.5;
      }
      Text(std::to_string(playerScore), 20.0f, Text::charHeight).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f)).render_text();
      Text(std::to_string(enemyScore), WINDOW_WIDTH * 0.95, Text::charHeight).set_vars_for_render(textShader, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f)).render_text();
      gameplay_controls();
      handle_gameplay_logic();
      break;
    case EXIT:
      exit_game();
      break;
    default:
      exit_game();
    }
  };

  void destroy_window()
  {
    player.delete_buffers();
    enemy.delete_buffers();
    ball.delete_buffers();
    player.shader.remove();
    textShader.remove();
    enemy.shader.remove();
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

  void gameplay_controls()
  {
    int tab_key = glfwGetKey(window, GLFW_KEY_TAB);
    if (tab_key == GLFW_PRESS && !is_tab_pressed)
    {
      is_tab_pressed = true;
      is_wireframe_mode = !is_wireframe_mode;
      if (is_wireframe_mode)
      {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      }
      else
      {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      }
    }

    if (tab_key == GLFW_RELEASE)
    {
      is_tab_pressed = false;
    }

    int w_key = glfwGetKey(window, GLFW_KEY_W);
    int s_key = glfwGetKey(window, GLFW_KEY_S);
    if (w_key == GLFW_PRESS)
    {
      if (player.position.y > 0)
      {
        inputPos.y = -1;
      }
      else
      {
        inputPos.y = -0;
      }
    }
    if (s_key == GLFW_PRESS)
    {
      if (player.position.y < WINDOW_HEIGHT - player.scale.y / 2.5)
      {
        inputPos.y = 1;
      }
      else
      {
        inputPos.y = 0;
      }
    }
    if (w_key == GLFW_RELEASE && s_key == GLFW_RELEASE)
    {
      inputPos.y = 0;
    }

    int escape_key = glfwGetKey(window, GLFW_KEY_ESCAPE);
    if (escape_key == GLFW_PRESS && !is_esc_pressed)
    {
      is_esc_pressed = true;
      setDeltaTime(0.0f);
    }
    if (escape_key == GLFW_RELEASE)
    {
      is_esc_pressed = false;
      setDeltaTime(1.0f);
    }
  };

  void exit_game()
  {
    glfwSetWindowShouldClose(window, true);
  }
};

#endif