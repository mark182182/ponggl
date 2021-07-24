#ifndef BALL_H
#define BALL_H

#include "entity.h"
#include "../shaders/shader.h"
#include "../projection.h"
#include "../audio.h"
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>

class Ball : public Entity
{
  using Entity::Entity;
  bool isColliding = false;
  Audio audio;

public:
  void set_audio(Audio &_audio)
  {
    audio = _audio;
  };
  void handle_logic(float deltaTime, Player player, Enemy enemy, float &xDir, float &yDir, float &prevPositionX, float &prevPositionY)
  {
    if (std::round(position.y) > WINDOW_HEIGHT - scale.y / 4 && std::round(position.y) < WINDOW_HEIGHT)
    {
      yDir = -1 * deltaTime;
      play_random_sfx();
    }
    else if (std::round(position.y) < scale.y / 4 && std::round(position.y) > 0)
    {
      yDir = 1 * deltaTime;
      play_random_sfx();
    }

    if (check_collision(*this, player))
    {
      if (prevPositionX - normPos.x < 0)
      {
        xDir = deltaTime;
        yDir += std::rand() % 2 - 1;
        play_random_sfx();
      }
    }
    else if (check_collision(*this, enemy))
    {
      if (prevPositionX - normPos.x > 0)
      {
        xDir = -1 * deltaTime;
        yDir += std::rand() % 2 - 1;
        play_random_sfx();
      }
    }

    position.x = position.x + xDir;
    position.y = position.y + yDir;

    shader.set_uniform_matrix4_value("model", 1, model);
    shader.set_uniform_matrix4_value("projection", 1, projection);
    shader.set_float_3("textColor", glm::vec3(1.0f, 1.0f, 1.0f));
    bind();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
    model = glm::scale(model, glm::vec3(scale.x, scale.y, 0.0f));
    draw();
    unbind();
    shader.set_uniform_matrix4_value("model", 1, model);
  };

private:
  void play_random_sfx()
  {
    int sfxNum = std::round(std::rand() % 8 + 1);
    audio.playSfx("audio/" + std::to_string(sfxNum) + ".mp3");
  }
};

#endif