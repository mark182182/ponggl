#include "common.h"
#include "game.h"
#include "game_state.h"
#include "window.h"

Game game;

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
    calculate_delta_time();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    game.update_game_logic();
    // Swap front and back buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  game.destroy_window();
  glfwTerminate();
  return 0;
};