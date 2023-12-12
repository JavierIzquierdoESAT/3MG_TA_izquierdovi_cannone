#pragma once
#include "AL/al.h"
#include "AL/alc.h"
#include <string>
#include <optional>

/*
* Struct that holds the RIFF data of the Wave file.
* The RIFF data is the meta data information that holds,
* the ID, size and format of the wave file
*/
struct RIFF_Header {
    char chunkID[4];
    long chunkSize;  //size not including chunkSize or chunkID
    char format[4];
};

/*
* Struct to hold fmt subchunk data for WAVE files.
*/
struct WAVE_Format {
    char subChunkID[4];
    long subChunkSize;
    short audioFormat;
    short numChannels;
    long sampleRate;
    long byteRate;
    short blockAlign;
    short bitsPerSample;
};

/*
* Struct to hold the data of the wave file
*/
struct WAVE_Data {
    char subChunkID[4];  //should contain the word data
    long subChunk2Size;  //Stores the size of the data block
};



class SoundBuffer {
 public:
  static std::optional<SoundBuffer> MakeBuffer(const std::string filename);
  SoundBuffer(SoundBuffer&& b);
  SoundBuffer(const SoundBuffer& b) = default;
  ALuint getBuffer();
  int Fequency();
  int Size();
  int Format();
  ~SoundBuffer();

  bool active_;

 private:
  SoundBuffer();

  ALuint buffer_;
  ALsizei size_;
  ALsizei frequency_;
  ALenum format_;
  std::string name_;
};
