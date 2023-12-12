#pragma once

#include <assert.h>

#include <optional>
#include <ranges>
#include <vector>

#include "GL/glew.h"
#include "ecs/component_manager.hpp"
#include "math/vector_3.h"

void RenderSystem(std::vector<std::optional<Position>>& positions,
                   std::vector<std::optional<Render>>& render) {
  auto p = positions.begin();
  auto r = render.begin();

  for (; p != positions.end(); p++, r++) {
    if (!p->has_value() || !r->has_value()) continue;
    auto& pv = p->value();
    auto& rv = r->value();

    float posToArr[3] = {pv.pos.x, pv.pos.y, pv.pos.z};
    rv.shaderProgram.setUniformValue(DataType::FLOAT_3, posToArr, "position");
    float colToArr[3] = {1,0,1};
    rv.shaderProgram.setUniformValue(DataType::FLOAT_3, colToArr,
                                      "initialUniform");

    rv.buffer.bindBuffer(Buffer::Target::kTarget_Vertex_Data);
    rv.buffer.bindVertexArray();
    rv.index_buffer.bindBuffer(Buffer::Target::kTarget_Elements);

    // TODO: parametrize indices
    glDrawElements(GL_TRIANGLES, rv.index_buffer.size() / sizeof(short int), GL_UNSIGNED_SHORT, 0);
    //glBindVertexArray(0);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    // Render
  }
  assert(r == render.end());
}

void SoundSystem(ComponentListCompact<AudioSource> &audio,
                 ComponentListSparse<Position>& positions) {

    for (auto& [e, audio_comp] : audio) {

      if (positions.at(e)->has_value()) {

         Position& pos_comp = positions.at(e)->value();
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

void CircleMoveSystem(ComponentListSparse<Position>& positions,
                      ComponentListSparse<AI>& ai_cmp) {
  auto p_it = positions.begin();
  auto ai_it = ai_cmp.begin();
  for (; p_it != positions.end() && ai_it != ai_cmp.end(); ++p_it, ++ai_it) {
    if (!p_it->has_value() || !ai_it->has_value()) continue;
    auto& pv = p_it->value();
    auto& aiv = ai_it->value();

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
