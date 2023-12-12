#pragma once
#include <string>

#include "AL/al.h"
#include "AL/alc.h"

class SoundBuffer;

class SoundSource {
 public:
  SoundSource(std::string name, ALfloat pos[3], ALfloat speed[3],
              float gain = 1.0f, float pitch = 1.0f);
  ~SoundSource();
  SoundSource(const SoundSource& other);
  SoundSource& operator=(const SoundSource& src) = default;
  SoundSource(SoundSource& other) noexcept;
  SoundSource(SoundSource&& other) noexcept;

  void setLoop(bool state);
  void setPos(ALfloat pos[3]);
  ALfloat* getPos();
  void setVelocity(ALfloat speed[3]);
  ALfloat* getVelocity();
  void updatePos(ALfloat pos[3]);
  void updateGain(float gain);
  void updatePitch(float pitch);
  void setGain(float gain);
  void setPitch(float pitch);

  float Gain() const;
  float Pitch() const;
  bool Loop() const;
  int Source() const;

  bool addSound(SoundBuffer* b);
  void unbindSound();
  bool isPlaying();
  void Play();
  void Stop();
  std::string Name();

  bool start_;
  bool stop_;

  bool destructible_;

 private:
  std::string name_;
  ALfloat pos_[3];
  ALfloat speed_[3];
  float gain_;
  float pitch_;
  bool loop_;

  bool isPlaying_;

  ALuint src_;
};
