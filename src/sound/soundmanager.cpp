#include "sound/soundmanager.h"
#include "sound/soundsource.h"
#include "sound/soundbuffer.h"
#include "imgui.h"



SoundManager::SoundManager() 
{
    // Open device and create context
    device_ = alcOpenDevice(NULL);
    ctx_ = alcCreateContext(device_, NULL);
    alcMakeContextCurrent(ctx_);

    src_manager_.clear();

}

SoundManager::~SoundManager()
{
    alcCloseDevice(device_);
}

void SoundManager::addsrc(SoundSource& s)
{
    src_manager_.push_back(std::move(s));
    s.destructible_ = true;

}


