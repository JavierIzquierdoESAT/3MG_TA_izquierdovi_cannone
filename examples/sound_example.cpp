#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "sound/soundbuffer.h"
#include "sound/soundsource.h"
#include "sound/soundmanager.h"
#include "ecs/component_manager.hpp"
#include "ecs/default_systems.hpp"
#include <vector>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"


#include "window.hpp"
#include "engine.hpp"


int main(int argv, char** args) {

    Engine engine;
    Window window = Window::Make(engine, 640, 480, "ventana");


    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui_ImplGlfwGL3_Init(window.GetWindow(), true);
    ImGui::StyleColorsDark();

    // Setup Dear ImGui context
    SoundManager m;
    ComponentManager component_manager;

    component_manager.addComponentClass<AudioSource>(ComponentListType::kCompact);

    ALfloat a[] = { 0,0,0 };
    ALfloat b[] = { 0,0,0 };
    AudioSource audio("Other", a, b, 1.0f);
    AudioSource audio2("Source 2", a, b, 1.0f);

    SoundBuffer buf = SoundBuffer::MakeBuffer("../assets/Invaders-CivilWar/other.wav").value();

    audio.src.addSound(&buf);
    audio2.src.addSound(&buf);

    Position p(0.0f, 0.0f, 0.0f);
    audio.src.start_ = true;
    audio.src.stop_ = false;

    audio2.src.start_ = true;
    audio2.src.stop_ = false;

    component_manager.addEntity<Position, AudioSource>(p, audio);
    component_manager.addEntity<Position, AudioSource>(p, audio2);

    


    while (!window.isDone()) {

        // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplGlfwGL3_NewFrame();


        SoundSystem(component_manager.getCompactIterator<AudioSource>(),
                    component_manager.getIterator<Position>());


        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        window.update();
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    UnbindSoundSystem(component_manager.getCompactIterator<AudioSource>());

    return 0;
}