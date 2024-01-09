#include <vector>

class ImguiProp {
 public:
  ImguiProp();
  ~ImguiProp();
  void AddNewTrack(class ComponentManager& m);

  float pos_[3];
  float speed_[3];
  float aux_gain_;
  float aux_pitch_;
  char name_[255];
  char root_[255];

private:
  std::vector<class SoundBuffer> myBuff_;

};
