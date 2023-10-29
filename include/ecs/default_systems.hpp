#include "ecs/component_manager.hpp"

void render_system(std::vector<std::optional<Position>>& positions,
                   std::vector<std::optional<Render>>& render) {
  auto p = positions.begin();
  auto r = render.begin();

  // TODO: Render Manager so that we dont need to call Buffer

  // TODO: buffer creation
  for (; p != positions.end(); p++, r++) {
    if (!p->has_value() || !r->has_value()) continue;
    auto& pv = p->value();
    auto& rv = r->value();

    std::vector<Vec3> transformedPos;
    // Transform
    for (auto& pos : rv.pos) {
      transformedPos.emplace_back(pos + pv.pos);
    }

    // TODO: Pass render data to buffer

    // Render
  }
  assert(r == render.end());
}