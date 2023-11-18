#include "window.hpp"

#include <array>
#include <iostream>
#include <string>
#include <unordered_map>

#include "Input.hpp"
#include "ecs/component_manager.hpp"
#include "ecs/default_systems.hpp"
#include "engine.hpp"
#include "shader_manager.hpp"
#include "time.hpp"
#include "triangle.hpp"

int WindowTutorial() {
  Engine engine;
  Window window = Window::Make(engine, 640, 480, "ventana");
  while (!window.isDone()) {
    window.update();
  }
  return 0;
}

int TriangleTutorial() {
  Engine engine;
  Window window = Window::Make(engine, 640, 480, "ventana");

  //++++++++++++++++++++++++
  ComponentManager component_manager;
  Position pos(0.0f, 0.0f, 0.0f);
  ShaderManager shader_program =
      ShaderManager::MakeShaders("../assets/col.fs", "../assets/col.vs")
          .value();
  Render ren =
      Render::MakeTriangle(0.5f, Vec3(1.0f, 0.0f, 0.0f), shader_program);
  unsigned triangle = component_manager.addEntity<Position, Render>(pos, ren);
  //++++++++++++++++++++++++

  while (!window.isDone()) {
    //++++++++++++++++++++++++
    RenderSystem(component_manager.getAll<Position>(),
                 component_manager.getAll<Render>());
    //++++++++++++++++++++++++

    window.update();
  }

  return 0;
}

// TODO: bug second input not working
InputButtonMap inputMap{
    {"Up", {InputButton::W, InputButton::UP}},
    {"Down", {InputButton::S, InputButton::DOWN}},
    {"Left", {InputButton::A, InputButton::LEFT}},
    {"Right", {InputButton::D, InputButton::RIGHT}},
};

int InputTutorial() {
  Engine engine;
  Window window = Window::Make(engine, 640, 480, "ventana");
  //++++++++++++++++++++++++
  InputManager input(window, inputMap);
  //++++++++++++++++++++++++

  ComponentManager component_manager;
  Position pos(0.0f, 0.0f, 0.0f);
  ShaderManager shader_program =
      ShaderManager::MakeShaders("../assets/col.fs", "../assets/col.vs")
          .value();
  Render ren =
      Render::MakeTriangle(0.5f, Vec3(1.0f, 0.0f, 0.0f), shader_program);
  unsigned triangle = component_manager.addEntity<Position, Render>(pos, ren);

  while (!window.isDone()) {
    //++++++++++++++++++++++++
    float speed = 0.3f;
    Position* trianglePos = component_manager.getComponent<Position>(triangle);
    if (input.buttonPressed("Up")) {
      trianglePos->pos.y += speed * Time::DeltaTime();
    }
    if (input.buttonPressed("Down")) {
      trianglePos->pos.y -= speed * Time::DeltaTime();
    }
    if (input.buttonPressed("Left")) {
      trianglePos->pos.x -= speed * Time::DeltaTime();
    }
    if (input.buttonPressed("Right")) {
      trianglePos->pos.x += speed * Time::DeltaTime();
    }
    //++++++++++++++++++++++++

    RenderSystem(component_manager.getAll<Position>(),
                 component_manager.getAll<Render>());

    window.update();
  }

  return 0;
}

int main(int, char**) {
  WindowTutorial();
  TriangleTutorial();
  InputTutorial();

  Engine engine;
  // TODO: maybe we don't need the make anymore
  Window window = Window::Make(engine, 640, 480, "ventana");
  InputManager input(window, inputMap);

  ComponentManager component_manager;
  Position pos(0.0f, 0.0f, 0.0f);
  // TODO: this should not be needed just an option
  // maybe we can use Engine to create some shader programs
  ShaderManager shader_program =
      ShaderManager::MakeShaders("../assets/col.fs", "../assets/col.vs")
          .value();
  Render ren =
      Render::MakeTriangle(0.5f, Vec3(1.0f, 0.0f, 0.0f), shader_program);
  unsigned triangle = component_manager.addEntity<Position, Render>(pos, ren);

  while (!window.isDone()) {
    
    Position* trianglePos = component_manager.getComponent<Position>(triangle);
    if (input.buttonDown("Left")) trianglePos->pos = Vec3(-0.5f, 0.0f, 0.0f);
    if (input.buttonDown("Right")) trianglePos->pos = Vec3(0.5f, 0.0f, 0.0f);

    RenderSystem(component_manager.getAll<Position>(),
                 component_manager.getAll<Render>());

    window.update();
  }

  return 0;
}
