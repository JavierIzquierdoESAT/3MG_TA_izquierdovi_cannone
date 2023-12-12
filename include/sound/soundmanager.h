#pragma once
#include <vector>
#include <string>
#include "AL/al.h"
#include "AL/alc.h"


enum ErrorCode {
  kErrorCode_OK = 0,
  kErrorCode_InvalidSourceName = -1,
};

class SoundSource;

class SoundManager {
public:
    SoundManager();
    ~SoundManager();


    void addsrc(SoundSource& s);

private:
    ALCdevice* device_;
    ALCcontext* ctx_;

    std::vector<SoundSource> src_manager_;


};