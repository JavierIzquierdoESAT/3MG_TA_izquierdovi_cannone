#pragma once

#include <assert.h>

#include <optional>
#include <vector>

#include "GL/glew.h"
#include "ecs/default_components.hpp"
#include "math/vector_3.h"

void render_system(std::vector<std::optional<Position>>& positions,
                   std::vector<std::optional<Render>>& render) {
  auto p = positions.begin();
  auto r = render.begin();

  for (; p != positions.end(); p++, r++) {
    if (!p->has_value() || !r->has_value()) continue;
    auto& pv = p->value();
    auto& rv = r->value();

    float posToArr[3] = {pv.pos.x, pv.pos.y, pv.pos.z};
    rv.shaderProgram->setUniformValue(DataType::FLOAT_3, posToArr,
                                      "position");
    float colToArr[3] = {rv.color[0].x, rv.color[0].y, rv.color[0].z};
    rv.shaderProgram->setUniformValue(DataType::FLOAT_3, colToArr,
                                    "initialUniform");
    // TODO: parametrize indices
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // Render
  }
  assert(r == render.end());
}

void CircleMoveSystem(std::vector<std::optional<Position>>& positions,
                      std::vector<std::optional<AI>>& ai_cmp) {
  auto p = positions.begin();
  auto ai = ai_cmp.begin();

  for (; p != positions.end(); p++, ai++) {
    if (!p->has_value() || !ai->has_value()) continue;
    auto& pv = p->value();
    auto& aiv = ai->value();

    aiv.counter++;
    if (aiv.counter > 20) {
      aiv.right = !aiv.right;
      aiv.counter = 0;
    }
    if (aiv.right)
      pv.pos.x += 0.005f;
    else
      pv.pos.x -= 0.005f;
  }
}