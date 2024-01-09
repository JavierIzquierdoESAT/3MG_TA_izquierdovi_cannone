#include "sound/soundsource.h"

#include <stdio.h>
#include <stdlib.h>

#include "..\..\include\sound\soundsource.h"
#include "sound/soundbuffer.h"

SoundSource::SoundSource(std::string name, ALfloat pos[3], ALfloat speed[3],
                         float gain, float pitch)
    : name_{name},
      gain_{gain},
      pitch_{pitch},
      destructible_{true},
      loop_{false},
      start_{false},
      stop_{true},
      isPlaying_{false} {
  alGetError();
  alGenSources(1, &src_);
  ALenum e = alGetError();
  if (e != AL_NO_ERROR) {
    fprintf(stderr, "Failed to create OpenAL source!\n");
    // handle errors
  }

  pos_[0] = pos[0];
  pos_[1] = pos[1];
  pos_[2] = pos[2];

  speed_[0] = speed[0];
  speed_[1] = speed[1];
  speed_[2] = speed[2];

  alSourcef(src_, AL_PITCH, pitch_);
  alSourcef(src_, AL_GAIN, gain_);
  alSourcefv(src_, AL_POSITION, pos);
  alSourcefv(src_, AL_VELOCITY, speed);
  alSourcei(src_, AL_LOOPING, 0);
  alSourcei(src_, AL_SOURCE_RELATIVE, AL_TRUE);
}

void SoundSource::setLoop(bool state) {
  loop_ = state;
  alSourcei(src_, AL_LOOPING, state);
}

void SoundSource::setPos(ALfloat pos[3]) {
  pos_[0] = pos[0];
  pos_[1] = pos[1];
  pos_[2] = pos[2];
  alSourcefv(src_, AL_POSITION, pos_);
}

ALfloat* SoundSource::getPos() { return pos_; }

void SoundSource::setVelocity(ALfloat speed[3]) {
  speed_[0] = speed[0];
  speed_[1] = speed[1];
  speed_[2] = speed[2];
  alSourcefv(src_, AL_VELOCITY, speed_);
}

ALfloat* SoundSource::getVelocity() { return speed_; }

void SoundSource::updatePos(ALfloat pos[3]) {
  pos_[0] += pos[0];
  pos_[1] += pos[1];
  pos_[2] += pos[2];

  alSourcefv(src_, AL_POSITION, pos_);
}

void SoundSource::setGain(float gain) {
  gain_ = gain;
  alSourcef(src_, AL_GAIN, gain_);
}

void SoundSource::setPitch(float pitch) {
  pitch_ = pitch;
  alSourcef(src_, AL_PITCH, pitch_);
}

float SoundSource::Gain() const { return gain_; }

float SoundSource::Pitch() const { return pitch_; }

bool SoundSource::Loop() const { return loop_; }

void SoundSource::updateGain(float gain) {
  gain_ += gain;
  alSourcef(src_, AL_GAIN, gain_);
}

void SoundSource::updatePitch(float pitch) {
  pitch_ += pitch;
  alSourcef(src_, AL_PITCH, pitch_);
}

int SoundSource::Source() const { return src_; }

bool SoundSource::addSound(SoundBuffer* b) {
  alSourcei(src_, AL_BUFFER, b->getBuffer());
  b->active_ = false;

  if (alGetError() != AL_NO_ERROR) {
    fprintf(stderr, "Fail add sound!\n");
    return false;
  }
  return true;
}

void SoundSource::unbindSound() {
  alSourceStop(src_);
  alSourcei(src_, AL_BUFFER, NULL);
}

void SoundSource::Play() {
  isPlaying_ = true;
  start_ = false;
  alSourcePlay(src_);
}

void SoundSource::Stop() {
  alSourceStop(src_);
  isPlaying_ = false;
  stop_ = true;
}

std::string SoundSource::Name() { return name_; }

bool SoundSource::isPlaying() {
  ALenum state;
  alGetSourcei(src_, AL_SOURCE_STATE, &state);
  return (state == AL_PLAYING);
}

SoundSource::~SoundSource() {
  if (destructible_) {
    alDeleteSources(1, &src_);
  }
}

SoundSource::SoundSource(SoundSource& other) noexcept
    : src_{other.src_},
      name_{other.name_},
      gain_{other.gain_},
      pitch_{other.pitch_},
      pos_{other.pos_[0], other.pos_[1], other.pos_[2]},
      speed_{other.speed_[0], other.speed_[1], other.speed_[2]},
      destructible_{true},
      loop_{other.loop_},
      start_{other.start_},
      stop_{other.stop_},
      isPlaying_{other.isPlaying_} {
  
  other.destructible_ = false;
}

SoundSource::SoundSource(SoundSource&& other) noexcept
    : src_{other.src_},
      name_{other.name_},
      gain_{other.gain_},
      pitch_{other.pitch_},
      pos_{other.pos_[0], other.pos_[1], other.pos_[2]},
      speed_{other.speed_[0], other.speed_[1], other.speed_[2]},
      destructible_{true},
      loop_{other.loop_},
      start_{other.start_},
      stop_{other.stop_},
      isPlaying_{other.isPlaying_} {
  other.destructible_ = false;
}
