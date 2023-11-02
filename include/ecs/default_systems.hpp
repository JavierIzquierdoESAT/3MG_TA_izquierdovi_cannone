#pragma once

#include <assert.h>

#include <optional>
#include <vector>

#include "ecs/default_components.hpp"
#include "math/vector_3.h"

#include "GL/glew.h"

void render_system(std::vector<std::optional<Position>>& positions,
                   std::vector<std::optional<Render>>& render) {
  auto p = positions.begin();
  auto r = render.begin();

  for (; p != positions.end(); p++, r++) {
    if (!p->has_value() || !r->has_value()) continue;
    auto& pv = p->value();
    auto& rv = r->value();

    std::vector<Vec3> transformedPos;
    // Transform
    for (auto& pos : rv.pos) {
      transformedPos.emplace_back(pos + pv.pos);
    }

  // TODO: parametrize indices
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // Render
  }
  assert(r == render.end());
}