#include "common.h"
#include "shaders/shader.h"
#include "texture.h"
#include "projection.h"
#include "text.h"
#include "audio.h"
#include "game.h"
#include "game_state.h"
#include "window.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <fstream>
#include <iostream>
#include <stb_image.h>

Game game;

void destroy_window()
{
  game.player.delete_buffers();
  game.enemy.delete_buffers();
  game.ball.delete_buffers();
  game.player.shader.remove();
  game.textShader.remove();
  game.enemy.shader.remove();
  glfwTerminate();
}

int main()
{
  if (!init())
  {
    return -1;
  };
  Game game = Game();
  game.init_shaders();
  game.init_shader_vars();
  game.init_entities();
  GameState::set_state(State::MENU);

  stbi_set_flip_vertically_on_load(true);

  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  while (!glfwWindowShouldClose(window))
  {
    float currentFrame = glfwGetTime();
    deltaTime = (currentFrame - lastFrame);
    lastFrame = currentFrame;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    game.update_game_logic();
    // Swap front and back buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  destroy_window();
  return 0;
}