# FirstSteps
## Creating a Window
- Initalize Engine
- Create Window
- Loop the program
- Update window and Engine

```cpp
#include "engine.hpp"
#include "window.hpp"

int main(int, char**) {
  Engine e;
  Window window = Window::Make(e, 640, 480, "ventana");
  while (!window.isDone()) {
    window.swap();
    e.update();
  }
  return 0;
}
```

## Drawing a triangle

ECS introducction: we use ECS to work with the in game entities, this means that and entity in our game is just a set of components to updates this entity we use systems wich use the component to perform operations. you are able to create you own components and systems but we have a bunch of default components and sytems to help you do basic stuff.

for rendering we will need to use the RenderSytem wich takes a Position component and a Render component, so we will need to create a new entity with this 2 components

 - create ComponentManager
 - create Position component
 - create Render component
 - create the entity

```cpp
  ShaderManager shader_program =
      ShaderManager::MakeShaders("../assets/col.fs", "../assets/col.vs")
          .value();

  ComponentManager component_manager;
  Position pos(0.0f, 0.0f, 0.0f);
  Render ren =
      Render::MakeTriangle(0.5f, Vec3(1.0f, 0.0f, 0.0f), shader_program);
  unsigned triangle = component_manager.addEntity<Position, Render>(pos, ren);
```
we now have a renderable entity, with that inisde our loop we can call the RenderSystem wich will draw all renderable entities added to the component manager.
```cpp
  while (!window.isDone()) {
    render_system(component_manager.getAll<Position>(),
                  component_manager.getAll<Render>());

    window.swap();
    engine.update();
  }
```

## Moving With Input

the first thing to do will be initialize the input system

we have implemented an action based input system, this means we have no interface to directly detect specific keys pressed instead you'll have to define wich keys you'll want to use for each action in yout game you can do so by creating an InputButtonMap, wich is just a map with strings as keys and a vector of inputs as values

```cpp
InputButtonMap inputMap{
    {"Up", {InputButton::W, InputButton::UP}},
    {"Down", {InputButton::S, InputButton::DOWN}},
    {"Left", {InputButton::A, InputButton::LEFT}},
    {"Right", {InputButton::D, InputButton::RIGHT}},
};
```
with that we can now create our InputManager object, it needs to be created by a window 

```cpp
InputManager input = window.addInputManager(inputMap);
```

in order to see that the input is working we will set the position of the triangle on the push of a button.
 - get position component of our triangle
 - check the state of an action
 - update the component

remember, to move independently of the frame rate you will need to use the time of the las frame, for that we offer Time::deltaTime() wich get updated with the engine update

```cpp
float speed = 0.3f;
Position* trianglePos = component_manager.getComponent<Position>(triangle);

if (input.buttonPressed("Up"))
  trianglePos->pos.y += speed * Time::delta_time();
if (input.buttonPressed("Down"))
  trianglePos->pos.y -= speed * Time::delta_time();
if (input.buttonPressed("Left"))
  trianglePos->pos.x -= speed * Time::delta_time();
if (input.buttonPressed("Right"))
  trianglePos->pos.x += speed * Time::delta_time();
```
 