#include "window.hpp"

#include <array>
#include <iostream>
#include <string>

#include "engine.hpp"
#include "buffer.hpp"
#include "shader_manager.hpp"
#include "time.hpp"
#include "load_obj.hpp"


int main(int, char**) {
    Engine e;

    auto w = Window::Make(e, 640, 480, "ventana");

    Buffer* obj = loadObj("../assets/javi.obj");
    auto shade = ShaderManager::MakeShaders("../assets/col.fs", "../assets/col.vs").value();

    if (w) {
        auto& window = w.value();

        while (!window.isDone()) {


            obj->bindVertexArray();
            shade.useProgram();
            window.swap();
            e.update();
        }
    }

    return 0;
}
