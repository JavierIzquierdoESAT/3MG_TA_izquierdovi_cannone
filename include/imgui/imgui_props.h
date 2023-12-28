#include <vector>

class ImguiProp {
 public:
  ImguiProp();
  ~ImguiProp();
  void AddNewTrack(class ComponentManager& m);

  float a[3];
  float b[3];
  float aux_gain;
  float aux_pitch;
  char name[255];
  char root[255];

private:
  std::vector<class SoundBuffer> myBuff;

};
