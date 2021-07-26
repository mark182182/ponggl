#ifndef AUDIO_H
#define AUDIO_H

#include <irrklang/irrKlang.h>
#include <iostream>
#include <vector>
#include <string>
using namespace irrklang;

class Audio
{
  ISoundEngine *SoundEngine;
  std::vector<irrklang::ISound *> sounds;

public:
  Audio()
  {
    SoundEngine = createIrrKlangDevice();
  };
  ~Audio(){};
  
  void playSfx(std::string path)
  {
    SoundEngine->play2D(path.c_str(), false);
  };
};

#endif