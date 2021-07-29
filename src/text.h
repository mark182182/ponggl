#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "shaders/shader.h"

struct Character
{
  unsigned int TextureID;
  glm::ivec2 Size;
  glm::ivec2 Bearing;
  unsigned int Advance;
};

static std::map<char, Character> Characters;
static unsigned int VAO, VBO;

class Text
{
public:
  static const unsigned int charHeight = 48;
  int width = 0;
  unsigned int numOfChars = 0;
  Shader s;
  std::string text;
  float x;
  float y;
  float scale;
  glm::vec3 color;

  Text(){};
  Text(std::string _text, float _x, float _y)
  {
    text = _text;
    width = _x;
    // TODO fix width
    width += _text.length() * (Characters['H'].Bearing.x + Characters['H'].Size.x + Characters['H'].Advance >> 6);
    x = _x;
    y = _y;
  };
  ~Text(){};

  void setShader(Shader &_s)
  {
    s = _s;
  }

  void setX(float _x)
  {
    x = _x;
  }

  void setY(float _y)
  {
    y = _y;
  }

  void setScale(float _scale)
  {
    scale = _scale;
  }

  void setColor(glm::vec3 _color)
  {
    color = _color;
  }

  Text set_vars_for_render(Shader &_s, float _scale, glm::vec3 _color)
  {
    s = _s;
    scale = _scale;
    color = _color;
    return *this;
  }

  void render_text()
  {
    float _x = x;
    // activate corresponding render state
    s.use();
    s.set_float_3("textColor", color);
    glBindVertexArray(VAO);
    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
      Character ch = Characters[*c];
      float xpos = _x + ch.Bearing.x * scale;
      float ypos = y + (Characters['H'].Bearing.y - ch.Bearing.y) * scale;
      float w = ch.Size.x * scale;
      float h = ch.Size.y * scale;
      // update VBO for each character
      float vertices[6][4] = {
          {xpos, ypos + h, 0.0f, 1.0f},
          {xpos + w, ypos, 1.0f, 0.0f},
          {xpos, ypos, 0.0f, 0.0f},
          {xpos, ypos + h, 0.0f, 1.0f},
          {xpos + w, ypos + h, 1.0f, 1.0f},
          {xpos + w, ypos, 1.0f, 0.0f}};
      // render glyph texture over quad
      glBindTexture(GL_TEXTURE_2D, ch.TextureID);
      // update content of VBO memory
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      // render quad
      glDrawArrays(GL_TRIANGLES, 0, 6);
      // advance cursors for next glyph (advance is 1/64 pixels)
      _x += (ch.Advance >> 6) * scale; // bitshift by 6 (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
  };
};

static void initText()
{
  FT_Library ft;
  if (FT_Init_FreeType(&ft))
  {
    std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
  }
  FT_Face face;
  if (FT_New_Face(ft, "fonts/firacode-regular.ttf", 0, &face))
  {
    std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
  }
  FT_Set_Pixel_Sizes(face, 0, Text::charHeight);
  if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
  {
    std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // no byte-alignment restriction
  for (unsigned char c = 0; c < 128; c++)
  {
    // load character glyph
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
      std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
      continue;
    }
    // generate texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer);
    // set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // now store character for later use
    unsigned int advanceX = face->glyph->advance.x;
    Character character = {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        advanceX};
    Characters.insert(std::pair<char, Character>(c, character));
  }
  FT_Done_Face(face);
  FT_Done_FreeType(ft);
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

#endif