#include "sound/soundbuffer.h"

SoundBuffer* SoundBuffer::MakeBuffer(const std::string filename) {
  SoundBuffer* b = new SoundBuffer();
  // Local Declarations
  FILE* soundFile = NULL;
  WAVE_Format wave_format;
  RIFF_Header riff_header;
  WAVE_Data wave_data;
  unsigned char* data;
  b->name_ = filename;
  soundFile = fopen(filename.c_str(), "rb");
  if (!soundFile) return nullptr;

  // Read in the first chunk into the struct
  fread(&riff_header, sizeof(RIFF_Header), 1, soundFile);

  // check for RIFF and WAVE tag in memeory
  if ((riff_header.chunkID[0] != 'R' || riff_header.chunkID[1] != 'I' ||
       riff_header.chunkID[2] != 'F' || riff_header.chunkID[3] != 'F') ||
      (riff_header.format[0] != 'W' || riff_header.format[1] != 'A' ||
       riff_header.format[2] != 'V' || riff_header.format[3] != 'E')) {
    fclose(soundFile);
    return nullptr;
  }

  // Read in the 2nd chunk for the wave info
  fread(&wave_format, sizeof(WAVE_Format), 1, soundFile);
  // check for fmt tag in memory
  if (wave_format.subChunkID[0] != 'f' || wave_format.subChunkID[1] != 'm' ||
      wave_format.subChunkID[2] != 't' || wave_format.subChunkID[3] != ' ') {
    fclose(soundFile);
    return nullptr;
  }

  // check for extra parameters;
  if (wave_format.subChunkSize > 16) fseek(soundFile, sizeof(short), SEEK_CUR);

  // Read in the the last byte of data before the sound file
  fread(&wave_data, sizeof(WAVE_Data), 1, soundFile);
  // check for data tag in memory
  if (wave_data.subChunkID[0] != 'd' || wave_data.subChunkID[1] != 'a' ||
      wave_data.subChunkID[2] != 't' || wave_data.subChunkID[3] != 'a') {
    fclose(soundFile);
    return nullptr;
  }

  // Allocate memory for data
  data = new unsigned char[wave_data.subChunk2Size];

  // Read in the sound data into the soundData variable
  if (!fread(data, wave_data.subChunk2Size, 1, soundFile)) {
    fclose(soundFile);
    return nullptr;
  }

  // Now we set the variables that we passed in with the
  // data from the structs
  b->size_ = wave_data.subChunk2Size;
  b->frequency_ = wave_format.sampleRate;
  // The format is worked out by looking at the number of
  // channels and the bits per sample.
  if (wave_format.numChannels == 1) {
    if (wave_format.bitsPerSample == 8)
      b->format_ = AL_FORMAT_MONO8;
    else if (wave_format.bitsPerSample == 16)
      b->format_ = AL_FORMAT_MONO16;
  } else if (wave_format.numChannels == 2) {
    if (wave_format.bitsPerSample == 8)
      b->format_ = AL_FORMAT_STEREO8;
    else if (wave_format.bitsPerSample == 16)
      b->format_ = AL_FORMAT_STEREO16;
  }
  // create our openAL buffer and check for success
  alGenBuffers(1, &b->buffer_);
  /*if (alGetError() != AL_NO_ERROR) {

      return nullptr;
  }*/

  // now we put our data into the openAL buffer and
  // check for success
  alBufferData(b->buffer_, b->format_, (void*)data, b->size_, b->frequency_);

  // clean up and return true if successful
  fclose(soundFile);
  delete[] data;
  return b;
}

SoundBuffer::SoundBuffer(SoundBuffer&& b)
    : buffer_{b.buffer_},
      active_{false},
      format_{b.format_},
      size_{b.size_},
      frequency_{b.format_} {
  b.active_ = false;
}

ALuint SoundBuffer::getBuffer() { return buffer_; }

int SoundBuffer::Fequency() { return frequency_; }

int SoundBuffer::Size() { return size_; }

int SoundBuffer::Format() { return format_; }

SoundBuffer::SoundBuffer()
    : active_{true}, buffer_{0}, format_{0}, size_{0}, frequency_{0} {}

SoundBuffer::~SoundBuffer() {
  if (!active_) {
    alDeleteBuffers(1, &buffer_);
  }
}
