#include "imgui/imgui_props.h"
#include "imgui/imgui.h"
#include "ecs/component_manager.hpp"
#include "sound/soundbuffer.h"

ImguiProp::ImguiProp()
    : pos_{0.0f, 0.0f, 0.0f},
      speed_{0.0f, 0.0f, 0.0f},
      aux_gain_{0.0f},
      aux_pitch_{0.0f},
      name_{""},
      root_{""} {}

ImguiProp::~ImguiProp() {
  
  for (auto& audioBuf : myBuff_) {
    audioBuf.active_ = false;
  }

}

void ImguiProp::AddNewTrack(ComponentManager& m) {


  
	 ImGui::Begin("New Sound");

    ImGui::InputText("Name", name_, 255);
    ImGui::InputText("Archive Root", root_, 255);
    
    ImGui::SliderFloat("Gain", &aux_gain_, 0.0f, 1.0f, "%.3f");
    

    
    ImGui::SliderFloat("Pitch", &aux_pitch_, 0.0f, 2.0f, "%.3f");


    ImGui::SliderFloat3("Position", pos_, -100.0f, 100.0f);

  
    // Create the components of audio
    if (ImGui::Button("Create")) {
      Position p(pos_[0], pos_[1], pos_[2]);
      AudioSource audio(name_, pos_, speed_, aux_gain_, aux_pitch_);
      SoundBuffer buf =
          SoundBuffer::MakeBuffer(root_).value();
      
      audio.src.addSound(&buf);
      buf.active_ = true;
      myBuff_.push_back(buf);
      audio.src.start_ = false;
      audio.src.stop_ = false;
      m.addEntity<Position, AudioSource>(p, audio);
    }
 
  ImGui::End();
  


}
