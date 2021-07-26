#include "const.h"
#include "shaders/shader.h"
#include "texture.h"
#include "projection.h"
#include "text.h"
#include "audio.h"
#include "game.h"
#include <GLFW/glfw3.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <fstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <stb_image.h>

const char *WINDOW_NAME = "PongGL";
GLFWwindow *window = NULL;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float prevPositionX = 0.0f;
float prevPositionY = 0.0f;

Game game;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void init_and_set_window_hints()
{
  std::cout << "Starting " << WINDOW_NAME << "..." << std::endl;
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int create_window_and_init_libs()
{
  window =
      glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);
  if (window == NULL)
  {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cerr << "Failed to init GLAD" << std::endl;
    return -1;
  }
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  return 1;
}

void bind_buffers(float vertices[], int vertices_size, unsigned int VBO,
                  unsigned int VAO)
{
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

int main()
{
  init_and_set_window_hints();
  int isInitSuccessful = create_window_and_init_libs();
  if (!isInitSuccessful)
  {
    return -1;
  }

  Game game = Game(window);
  game.init_shaders();
  game.init_entities();
  game.set_state(State::GAMEPLAY);

  std::cout << "Buffers are bound" << std::endl;

  stbi_set_flip_vertically_on_load(true);

  Texture woodTexture = Texture("textures/wood.jpg", GL_RGB, GL_REPEAT);
  Texture transparentTexture =
      Texture("textures/transparent.png", GL_RGBA, GL_REPEAT);

  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);

  std::cout << "Textures are set" << std::endl;

  game.init_shader_vars();

  while (!glfwWindowShouldClose(window))
  {
    float currentFrame = glfwGetTime();
    deltaTime = (currentFrame - lastFrame) * 60 * 4;
    lastFrame = currentFrame;
    prevPositionX = glm::normalize(glm::vec3(game.ball.position.x, game.ball.position.y, 0.0f)).x;
    prevPositionY = glm::normalize(glm::vec3(game.ball.position.x, game.ball.position.y, 0.0f)).y;
    game.set_delta_time(deltaTime);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::string posX = "X: ";
    posX.append(std::to_string(inputPos.x));
    std::string posY = "Y: ";
    posY.append(std::to_string(inputPos.y));

    // TODO fix textures, now we only have the color
    woodTexture.activiate_and_bind(GL_TEXTURE0);

    game.update_game_logic();
    game.render_text(std::to_string(game.playerScore), 20.0f, 10.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    game.render_text(std::to_string(game.enemyScore), WINDOW_WIDTH * 0.95, 10.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

    // Swap front and back buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  game.player.delete_buffers();
  game.enemy.delete_buffers();
  game.ball.delete_buffers();
  game.player.shader.remove();
  game.textShader.remove();
  game.enemy.shader.remove();
  glfwTerminate();
  return 0;
}