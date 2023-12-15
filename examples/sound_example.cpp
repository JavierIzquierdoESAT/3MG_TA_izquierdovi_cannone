#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "sound/soundbuffer.h"
#include "sound/soundsource.h"
#include "ecs/component_manager.hpp"
#include "ecs/default_systems.hpp"
#include <vector>

#include "window.hpp"
#include "engine.hpp"


int main(int argv, char** args) {

    Engine engine;
    Window window = Window::Make(engine, 640, 480, "ventana");

    ComponentManager component_manager;

    component_manager.addComponentClass<AudioSource>(ComponentListType::kCompact);

    ALfloat a[] = { 0,0,0 };
    ALfloat b[] = { 0,0,0 };
    AudioSource audio("Other", a, b, 1.0f);
    AudioSource audio2("Other 2", a, b, 1.0f);
    AudioSource audio3("Vocals", a, b, 1.0f);

    SoundBuffer buf =
        SoundBuffer::MakeBuffer("../assets/Invaders-CivilWar/other.wav")
            .value();
    SoundBuffer buf2 =
        SoundBuffer::MakeBuffer("../assets/Invaders-CivilWar/vocals.wav")
            .value();

    audio.src.addSound(&buf);
    audio2.src.addSound(&buf);
    audio3.src.addSound(&buf2);

    Position p(0.0f, 0.0f, 0.0f);
    audio.src.start_ = false;
    audio.src.stop_ = false;

    audio2.src.start_ = false;
    audio2.src.stop_ = false;

    audio3.src.start_ = false;
    audio3.src.stop_ = false;

    component_manager.addEntity<Position, AudioSource>(p, audio);
    component_manager.addEntity<Position, AudioSource>(p, audio2);
    component_manager.addEntity<Position, AudioSource>(p, audio3);

    


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