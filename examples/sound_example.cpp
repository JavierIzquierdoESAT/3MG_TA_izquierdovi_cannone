#include <stdio.h>
#include <stdlib.h>
#include <string>


#include "window.hpp"
#include "engine.hpp"

#include "sound/soundbuffer.h"
#include "sound/soundsource.h"
#include "sound/soundmanager.h"
#include "ecs/component_manager.hpp"
#include "ecs/default_systems.hpp"
#include <vector>




int main(int argv, char** args) {

    Engine engine;
    Window window = Window::Make(engine, 640, 480, "ventana");

    // Setup Dear ImGui context
    SoundManager m;
    ComponentManager component_manager;

    component_manager.addComponentClass<AudioSource>(ComponentListType::kCompact);

    ALfloat a[] = { 0,0,0 };
    ALfloat b[] = { 0,0,0 };
    AudioSource audio("Other", a, b, 1.0f);

    SoundBuffer buf = SoundBuffer::MakeBuffer("../assets/Invaders-CivilWar/other.wav").value();

    audio.src.addSound(&buf);

    Position p(0.0f, 0.0f, 0.0f);
    audio.src.start_ = true;
    audio.src.stop_ = false;

    component_manager.addEntity<Position, AudioSource>(p, audio);

    


    while (!window.isDone()) {

        // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        glClear(GL_COLOR_BUFFER_BIT);


        SoundSystem(component_manager.getCompactIterator<AudioSource>(),
                    component_manager.getIterator<Position>());


        window.update();
    }

    UnbindSoundSystem(component_manager.getCompactIterator<AudioSource>());

    return 0;
}