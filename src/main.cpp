#include "const.h"
#include "shaders/shader.h"
#include "texture.h"
#include "projection.h"
#include "text.h"
#include "entities/entity.h"
#include "entities/player.h"
#include "entities/enemy.h"
#include "entities/ball.h"
#include "audio.h"
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
bool wireframe_mode = false;
bool tab_pressed = false;
bool up_pressed = false;
bool down_pressed = false;
float fov_amount = 90.0f;
float prev_fov_amount = fov_amount;

float lastX = WINDOW_WIDTH / 2, lastY = WINDOW_HEIGHT / 2;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float prevPositionX = 0.0f;
float prevPositionY = 0.0f;

Player player;
Enemy enemy;
Ball ball;
Audio audio;

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

void process_Input(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  int tab_press = glfwGetKey(window, GLFW_KEY_TAB);

  if (tab_press == GLFW_PRESS && tab_pressed != true)
  {
    tab_pressed = true;
    wireframe_mode = !wireframe_mode;
    if (wireframe_mode)
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
  }
  if (tab_press == GLFW_RELEASE)
  {
    tab_pressed = false;
  }

  const float cameraSpeed = 1.008f;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    if (inputPos.y > 10.0f)
    {
      inputPos.y = cameraSpeed * (inputPos.y - 10.0f);
    }
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    if (inputPos.y < WINDOW_HEIGHT - player.scale.y / 2.5)
    {
      inputPos.y = cameraSpeed * (inputPos.y + 10.0f);
    }
  }
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

  audio = Audio();

  Shader defaultShader = Shader("shaders/vertex.vs", "shaders/fragment.fs");
  Shader enemyShader = Shader("shaders/vertex.vs", "shaders/fragment.fs");
  Shader ballShader = Shader("shaders/vertex.vs", "shaders/fragment.fs");
  Shader textShader = Shader("shaders/vertex.vs", "shaders/fragment.fs");

  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f);

  player = Player("player", defaultShader, projection, glm::vec2(WINDOW_WIDTH / 8, WINDOW_WIDTH / 4), inputPos);
  enemy = Enemy("enemy", enemyShader, projection, glm::vec2(WINDOW_WIDTH / 8, WINDOW_WIDTH / 4), glm::vec2(WINDOW_WIDTH * 0.8, WINDOW_HEIGHT * 0.5));
  ball = Ball("ball", ballShader, projection, glm::vec2(WINDOW_WIDTH / 8, WINDOW_WIDTH / 16), glm::vec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5));
  ball.set_audio(audio);

  initText();

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

  player.shader.use();
  player.shader.set_int("image", 0);
  // defaultShader.use();
  // defaultShader.set_int("image", 0);

  enemy.shader.use();
  enemy.shader.set_int("image", 0);

  ball.shader.use();
  ball.shader.set_int("image", 0);

  textShader.use();
  textShader.set_int("image", 0);

  float xDirection = -1;
  float yDirection = 0;

  while (!glfwWindowShouldClose(window))
  {
    float currentFrame = glfwGetTime();
    deltaTime = (currentFrame - lastFrame) * 60 * 4;
    lastFrame = currentFrame;
    prevPositionX = glm::normalize(glm::vec3(ball.position.x, ball.position.y, 0.0f)).x;
    prevPositionY = glm::normalize(glm::vec3(ball.position.x, ball.position.y, 0.0f)).y;

    process_Input(window);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::string posX = "X: ";
    posX.append(std::to_string(inputPos.x));
    std::string posY = "Y: ";
    posY.append(std::to_string(inputPos.y));

    // TODO fix textures, now we only have the color
    woodTexture.activiate_and_bind(GL_TEXTURE0);

    // textShader.set_uniform_matrix4_value("model", 1, glm::mat4(1.0f));
    // textShader.set_uniform_matrix4_value("projection", 1, projection);
    // RenderText(textShader, posX, 20.0f, inputPos.x, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    // RenderText(textShader, posY, 10.0f, 300.0f, 1.0f, glm::vec3(1.0f, 0.0f, 1.0f));

    player.handle_logic();
    enemy.handle_logic(ball);
    ball.handle_logic(deltaTime, player, enemy, xDirection, yDirection, prevPositionX, prevPositionY);

    // TODO remove ball and reset positions, if the ball enters this area
    if (ball.position.x <= WINDOW_WIDTH && ball.position.x >= WINDOW_WIDTH * 0.8 + enemy.scale.x / 4)
    {
      std::cout << "Enemy area" << std::endl;
    }

    if (ball.position.x >= 0 && ball.position.x <= WINDOW_WIDTH * 0.2 - player.scale.x / 4)
    {
      std::cout << "Player area" << std::endl;
    }
    // Swap front and back buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  player.delete_buffers();
  enemy.delete_buffers();
  ball.delete_buffers();
  defaultShader.remove();
  textShader.remove();
  enemyShader.remove();
  glfwTerminate();
  return 0;
}