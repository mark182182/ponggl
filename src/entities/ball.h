#ifndef BALL_H
#define BALL_H

#include "entity.h"

class Ball : public Entity
{
  using Entity::Entity;
  bool isColliding = false;

public:
  Audio audio;
  float speed = 400.0f;

  void set_audio(Audio &_audio)
  {
    audio = _audio;
  };

  void handle_logic(Player &player, Enemy &enemy, float &xDir, float &yDir)
  {
    if (std::round(position.y) > WINDOW_HEIGHT - scale.y / 4 && std::round(position.y) < WINDOW_HEIGHT)
    {
      yDir = -1;
      play_random_sfx();
    }
    else if (std::round(position.y) < scale.y / 4 && std::round(position.y) > 0)
    {
      yDir = 1;
      play_random_sfx();
    }

    if (check_collision(*this, player))
    {
      xDir = 1;
      yDir = std::rand() % 2 - 1.5;
      play_random_sfx();
    }
    else if (check_collision(*this, enemy))
    {
      xDir = -1;
      yDir = std::rand() % 4 - 2;
      play_random_sfx();
    }

    position.x += deltaTime * xDir * speed;
    position.y += deltaTime * yDir * speed;

    shader.set_uniform_matrix4_value("model", 1, model);
    shader.set_uniform_matrix4_value("projection", 1, projection);
    shader.set_float_3("textColor", glm::vec3(1.0f, 1.0f, 1.0f));
    texture.activiate_and_bind(GL_TEXTURE0);
    bind();
    update_position(position);
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