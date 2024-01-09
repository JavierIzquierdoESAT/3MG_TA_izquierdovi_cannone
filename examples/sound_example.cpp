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
#include "imgui/imgui_impl_glfw_gl3.h"
#include "imgui/imgui_props.h"


int main(int argv, char** args) {

    Engine engine;
    Window window = Window::Make(engine, 640, 480, "ventana");

    ComponentManager component_manager;
    //add the new type of component to the component manager
    component_manager.addComponentClass<AudioSource>(ComponentListType::kCompact);

    ALfloat a[] = { 0,0,0 };
    ALfloat b[] = { 0,0,0 };

    //Create the components of audio
    AudioSource audio("Other", a, b, 1.0f);
    AudioSource audio2("Other 2", a, b, 1.0f);
    AudioSource audio3("Vocals", a, b, 1.0f);

    //Inizilize sound buffers
    SoundBuffer buf =
        SoundBuffer::MakeBuffer("../assets/Invaders-CivilWar/other.wav")
            .value();
    SoundBuffer buf2 =
        SoundBuffer::MakeBuffer("../assets/Invaders-CivilWar/vocals.wav")
            .value();

    //Add buffers to the sources
    audio.src.addSound(&buf);
    audio2.src.addSound(&buf);
    audio3.src.addSound(&buf2);

    Position p(0.0f, 0.0f, 0.0f);
    //set the status of the sources
    audio.src.start_ = false;
    audio.src.stop_ = false;

    audio2.src.start_ = false;
    audio2.src.stop_ = false;

    audio3.src.start_ = false;
    audio3.src.stop_ = false;

    //Create the enyitys with than components
    component_manager.addEntity<Position, AudioSource>(p, audio);
    component_manager.addEntity<Position, AudioSource>(p, audio2);
    component_manager.addEntity<Position, AudioSource>(p, audio3);
    ImguiProp prop;
    


    while (!window.isDone()) {

        
      
        prop.AddNewTrack(component_manager);
        //Use the system to set the status od the audio comps
        SoundSystem(component_manager.getCompactList<AudioSource>(),
                    component_manager.getSparseList<Position>());


        window.renderImgui();
        window.update();
    
    }

    //unbid all the buffers from the sources before delete
    UnbindSoundSystem(component_manager.getCompactList<AudioSource>());

    return 0;
}