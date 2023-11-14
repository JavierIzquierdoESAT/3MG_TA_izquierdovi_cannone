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

    auto obj = loadObj("../assets/javi.obj").value();
    auto shade = ShaderManager::MakeShaders("../assets/obj.fs", "../assets/obj.vs").value();

    if (w) {
        auto& window = w.value();

        while (!window.isDone()) {

            float dt = Time::delta_time();
            shade.setUniformValue(DataType::FLOAT_1, &dt, "u_time");
            obj.bindVertexArray();
            shade.useProgram();
            glDrawArrays(GL_TRIANGLES, 0, obj.size());
            window.swap();
            e.update();
        }
    }

    return 0;
}
