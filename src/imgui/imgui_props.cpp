#include "imgui/imgui_props.h"
#include "imgui/imgui.h"
#include "ecs/component_manager.hpp"
#include "sound/soundbuffer.h"

ImguiProp::ImguiProp()
    : a{0.0f, 0.0f, 0.0f},
      b{0.0f, 0.0f, 0.0f},
      aux_gain{0.0f},
      aux_pitch{0.0f},
      name{""},
      root{""} {}

ImguiProp::~ImguiProp() {
  
  for (auto& a : myBuff) {
    a.active_ = false;
  }

}

void ImguiProp::AddNewTrack(ComponentManager& m) {


  
	 ImGui::Begin("New Sound");

    ImGui::InputText("Name", name, 255);
    ImGui::InputText("Archive Root", root, 255);
    
    ImGui::SliderFloat("Gain", &aux_gain, 0.0f, 1.0f, "%.3f");
    

    
    ImGui::SliderFloat("Pitch", &aux_pitch, 0.0f, 2.0f, "%.3f");


    ImGui::SliderFloat3("Position", a, -100.0f, 100.0f);

  
    // Create the components of audio
    if (ImGui::Button("Create")) {
      Position p(a[0], a[1], a[2]);
      AudioSource audio(name, a, b, aux_gain, aux_pitch);
      SoundBuffer buf =
          SoundBuffer::MakeBuffer(root).value();
      
      audio.src.addSound(&buf);
      buf.active_ = true;
      myBuff.push_back(buf);
      audio.src.start_ = false;
      audio.src.stop_ = false;
      m.addEntity<Position, AudioSource>(p, audio);
    }
 
  ImGui::End();
  


}
