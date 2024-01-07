# FirstSteps

In this tutorial we will walk you through the most basic stuff you can do with the engine, we won't go into much detail
of how each thing works but rather will give a template for starting your own project as well as linking to the detailed
explanation of each of these features.

* [Creating a Window](#creating-a-window)
* [Basic Drawing](#drawing-a-triangle)
* [Input](#moving-with-input)
* [Entity Component System](#entity-component-system)
  * Custom Components
  * Custom Systems
* Multi Thread

## Creating a Window

The most basic thing you need to use all the engine features is to initialize it by creating an [Engine]() object.

With the engine initialized you can create a window object and start the program main loop

It's important to update the engine and swap the window buffers for proper functioning of internal variables.

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

TODO: remove shader manager, will propbably go inside Rendere Component

For drawing we nee to use the [Entity Component System](#entity-component-system), we will explan later how this works but for now you only need to know that entities are a collection of components, data containers, and systems perform operations on all the components of a type.

to handle the entities and components we will use a [ComponentManager]() with it you can create and entity and asign it the desired componets for rendering we need an entity with at least a Position and Render component.

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
we have a drawable entity registered, to draw it, we need to call the render system.
```cpp
  while (!window.isDone()) {
    render_system(component_manager.getAll<Position>(),
                  component_manager.getAll<Render>());

    window.swap();
    engine.update();
  }
```
as we said earlier, systems operato on all the components, that's why the renderSystem doesn't need the entity, but rather component containers that we can retrieve form the ComponentManager.

## Moving With Input

to use the input you'll first need to set the acctions required by your game by creating an inputButtonMap, an InputButtonMap is a map with strings as keys, wich represent the action and a vector of inputs as values, wich represent the values for wich that action will be activated.

```cpp
InputButtonMap inputMap{
    {"Up", {InputButton::W, InputButton::UP}},
    {"Down", {InputButton::S, InputButton::DOWN}},
    {"Left", {InputButton::A, InputButton::LEFT}},
    {"Right", {InputButton::D, InputButton::RIGHT}},
};
```

with the map created we now neen to create an inputManager with it

```cpp
InputManager input = window.addInputManager(inputMap);
```

only thing left is to use it, for that we will update the position of the triangle on the main loop. we multiply by time::delta_time() to make the movement frame rate independant.

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
 
## Entity component system

this engine uses ecs to improve performance, wich is a bit different to object oriented programming, instead of having classes containing data and functionality, we have components (data) and systems (functionality), each component belongs to an entity.

this means that in your project, if you want a weapon, instead of creating a weapon class you will create an entity with a shooting component, and a system that will fire a bullet, the component could contain fire rate, entity to shoot, bullet position... and the system would get all shooting componentents that exist determine if they shoud spawn a bullet and spawn it. This is a super simplified example, but we will see some real examples further down.

Our engine already dontains some [Components]() and [Systems]() ready to use, but you'll need to add your own at some point.

**Entities**  
entities are just an unsigned int you don't need to worry about them, since they are handled by the component manger, you only may store an entity if you nee to access it outside a system, as we did in the input example. If you have an entity stored and you delete it using the component manager, using again that deleted entity will result in undefined behabiour.

### Custom Components
In order to add a new component to the engine first you need to create the struct or class with the needed data.
a struct is prefered since the goal of a component should be to hold data.

```cpp
struct InputComponent {
  InputManager* actions;
};

struct ControllerComponent {
  coma::Vec2 dir = coma::Vec2(0.0f, 0.0f);
  float speed = 0.3f;
};
```

with the struct we nown need to register it in the [ComponentManager]() 
```cpp
  component_manager.addComponentClass<InputComponent>(ComponentListType::kCompact);
  component_manager.addComponentClass<ControllerComponent>(ComponentListType::kCompact);
```
when adding a component you can specify if it's a sparse list or a compoact list, a compact list should be used if your component is going to be used on only a few of the total entities of the game, as in this example, only one entity is going to recieve input, may be 4 if it's multiplayer game. If you component is goinjg to be commonly used it should be a Sparse.

with tat the component is registered and ready to use.

### Custom Systems

a system is just a static function, in it you will want to do something with all the requiered components, for that there is ComponentIterator that you can use to easily go through all the needed components

```cpp
inline void CircleMoveSystem(ComponentListSparse<Position>& positions,
                      ComponentListSparse<AI>& ai_cmp)  {
  ComponentIterator it(positions, ai_cmp);
  while (it.next()) {
    auto [pv, aiv] = it.get();
  }
}
```

once you have your function you just call it on your main loop

```cpp
CircleMoveSystem(component_manager.getSparseList<Position>(),
                 component_manager.getSparseList<AI>());
```

note that to call the function and to create the function is impotant that you kow what type of ComponentList you are using.

> for better optimization the first list you pass to the ComponentIterator constructor should be list that contains the least total number of components.

> for even better optimization when you have lots of entities in your game you can not use the ComponentIterator and iterate the lists with a for loop, but that can complicate the system a little.