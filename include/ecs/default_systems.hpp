#pragma once

#include <assert.h>
#include <chrono>

#include <optional>
#include <ranges>
#include <vector>

#include "GL/glew.h"
#include "ecs/component_manager.hpp"
#include "math/vector_3.h"
#include "imgui/imgui.h"

inline void RenderSystem(ComponentListSparse<Position>& positions,
                  ComponentListSparse<Render>& render) {

  ComponentIterator it(positions, render);
  while (it.next()) {
    auto [pv, rv] = it.get();
    float posToArr[3] = {pv.pos.x, pv.pos.y, pv.pos.z};
    rv.shaderProgram.setUniformValue(DataType::FLOAT_3, posToArr, "position");
    float colToArr[3] = {1, 0, 1};
    rv.shaderProgram.setUniformValue(DataType::FLOAT_3, colToArr,
                                     "initialUniform");

    rv.buffer.bindBuffer(Buffer::Target::kTarget_Vertex_Data);
    rv.buffer.bindVertexArray();
    rv.index_buffer.bindBuffer(Buffer::Target::kTarget_Elements);

    // TODO: parametrize indices
    glDrawElements(GL_TRIANGLES, rv.index_buffer.size() / sizeof(short int),
                   GL_UNSIGNED_SHORT, 0);
    //glBindVertexArray(0);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    // Render
  }
}

void SoundSystem(ComponentListCompact<AudioSource> &audio,
                 ComponentListSparse<Position>& positions) {

    for (auto& [e, audio_comp] : audio) {

      if (positions.at(e)->has_value()) {

        Position& pos_comp = positions.at(e)->value();

        { 
          ImGui::Begin("Sound");
          ImGui::PushID(e);
          bool open = ImGui::CollapsingHeader(audio_comp.src.Name().c_str());
          if (open) {
            // ImGui::Text(audio_comp.src.Name().c_str());
            if (ImGui::Button("Stop")) {
              audio_comp.src.stop_ = true;
            }
            ImGui::SameLine();

            if (ImGui::Button("Play")) {
              audio_comp.src.start_ = true;
              audio_comp.src.stop_ = false;
            }

            bool muted = audio_comp.src.Gain() == 0;
            if (ImGui::Checkbox("Mute", &muted)) {
              muted ? audio_comp.src.setGain(0.0f)
                    : audio_comp.src.setGain(1.0f);
            }

            float aux_gain = audio_comp.src.Gain();
            ImGui::SliderFloat("Gain", &aux_gain, 0.0f, 1.0f, "%.3f");
            audio_comp.src.setGain(aux_gain);

            float aux_pitch = audio_comp.src.Pitch();
            ImGui::SliderFloat("Pitch", &aux_pitch, 0.0f, 2.0f, "%.3f");
            audio_comp.src.setPitch(aux_pitch);

            float* aux_pos = &pos_comp.pos.x;
            ImGui::SliderFloat3("Position", aux_pos, -100.0f, 100.0f);


            bool loop = audio_comp.src.Loop();
            if (ImGui::Checkbox("Loop", &loop)) {
              audio_comp.src.setLoop(loop);
            }
          }

          ImGui::PopID();

          ImGui::End();
        }

         
        audio_comp.src.setPos(&pos_comp.pos.x);
        
        if (!audio_comp.src.isPlaying() && audio_comp.src.start_) {
          audio_comp.src.Play();
        }

        if (audio_comp.src.isPlaying() && audio_comp.src.stop_) {
          audio_comp.src.Stop();
        }

      }

    }
}

//TODO:: Move to the destructor
void UnbindSoundSystem(ComponentListCompact<AudioSource>& audio) {
  for (auto& [e, audio_comp] : audio) {
    
    audio_comp.src.unbindSound();
    
  }
}



inline void CircleMoveSystem(ComponentListSparse<Position>& positions,
                      ComponentListSparse<AI>& ai_cmp)  {
  ComponentIterator it(positions, ai_cmp);
  while (it.next()) {
    auto [pv, aiv] = it.get();
    aiv.counter++;
    if (aiv.counter > 20) {
      aiv.right = !aiv.right;
      aiv.counter = 0;
    }
    if (aiv.right)
      pv.pos.x += 0.05f;
    else
      pv.pos.x -= 0.05f;
  }
}
