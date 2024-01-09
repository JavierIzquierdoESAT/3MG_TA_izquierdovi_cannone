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

void RenderSystem(ComponentListSparse<Position>& positions,
                         ComponentListSparse<Render>& render);

void SoundSystem(ComponentListCompact<AudioSource>& audio,
                 ComponentListSparse<Position>& positions);

//TODO:: Move to the destructor
void UnbindSoundSystem(ComponentListCompact<AudioSource>& audio)
{
    for (auto& [e, audio_comp] : audio)
    {
        audio_comp.src.unbindSound();
    }
}


void CircleMoveSystem(ComponentListSparse<Position>& positions,
                             ComponentListSparse<AI>& ai_cmp);
