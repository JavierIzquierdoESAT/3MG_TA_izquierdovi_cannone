#pragma once

#include <array>
#include <unordered_map>
#include <unordered_set>

struct GLFWwindow;
class Window;

/// @enum allowed input buttons
enum class InputButton {
  UNKNOWN = -1,

  MOUSE_LEFT = 0,
  MOUSE_RIGHT,
  MOUSE_MIDDLE,
  MOUSE_4,
  MOUSE_5,
  MOUSE_6,
  MOUSE_7,
  MOUSE_8,

  SCROLL_UP = 8,
  SCROLL_DOWN,

  SPACE = 32,
  APOSTROPHE = 39,
  COMMA = 44,
  MINUS = 45,
  PERIOD = 46,
  SLASH = 47,
  _0 = 48,
  _1,
  _2,
  _3,
  _4,
  _5,
  _6,
  _7,
  _8,
  _9,
  SEMICOLON = 59,
  EQUAL = 61,
  A = 65,
  B,
  C,
  D,
  E,
  F,
  G,
  H,
  I,
  J,
  K,
  L,
  M,
  N,
  O,
  P,
  Q,
  R,
  S,
  T,
  U,
  V,
  W,
  X,
  Y,
  Z,
  LEFT_BRACKET = 91,
  BACKSLASH = 92,
  RIGHT_BRACKET = 93,
  GRAVE_ACCENT = 96,
  WORLD_1 = 161,
  WORLD_2 = 162,
  ESCAPE = 256,
  ENTER,
  TAB,
  BACKSPACE,
  INSERT,
  DELETE,
  RIGHT,
  LEFT,
  DOWN,
  UP,
  PAGE_UP,
  PAGE_DOWN,
  HOME,
  END,
  CAPS_LOCK = 280,
  SCROLL_LOCK,
  NUM_LOCK,
  PRINT_SCREEN,
  PAUSE,
  F1 = 290,
  F2,
  F3,
  F4,
  F5,
  F6,
  F7,
  F8,
  F9,
  F10,
  F11,
  F12,
  F13,
  F14,
  F15,
  F16,
  F17,
  F18,
  F19,
  F20,
  F21,
  F22,
  F23,
  F24,
  F25,
  KP_0 = 320,
  KP_1,
  KP_2,
  KP_3,
  KP_4,
  KP_5,
  KP_6,
  KP_7,
  KP_8,
  KP_9,
  KP_DECIMAL,
  KP_DIVIDE,
  KP_MULTIPLY,
  KP_SUBTRACT,
  KP_ADD,
  KP_ENTER,
  KP_EQUAL,
  LEFT_SHIFT = 340,
  LEFT_CONTROL,
  LEFT_ALT,
  LEFT_SUPER,
  RIGHT_SHIFT,
  RIGHT_CONTROL,
  RIGHT_ALT,
  RIGHT_SUPER,
  MENU,
  LAST
};


/// @brief structure that binds user created actions and physical input
using InputButtonMap = std::unordered_map<std::string, std::vector<InputButton>>;

/// @brief allows for input state retrieval
///
/// this class is closely related to an InputButtonMap
/// this structure is a map with strings as keys and a vector of InputButton
/// as value,
/// so you should define your actions as the keys and any number of
/// buttons as value
///
/// ## example
/// ~~~~~~~~~~~~~~~.cpp
/// InputButtonMap inputMap{
///   {"Up", {InputButton::W, InputButton::DOWN}},
///   {"Down", {InputButton::S}},
///   {"Left", {InputButton::A}},
///   {"Right", {InputButton::D}},
/// }
/// ~~~~~~~~~~~~~~~
class InputManager {
 public:
  ~InputManager() = default;

  /// @brief creates and binds an input map
  /// @param w window handle reference
  /// @param m InputButtonMap to bind
  InputManager(const Window& window, InputButtonMap m);


  //TODO: try to make this only accessible to the window
  /// @brief updates the state of each key
  ///
  /// must be called once per frame for proper functioning of this class
  static void update();

  /// @brief checks if the any of the buttons asigned to an action have been
  /// *pressed* during the frame
  /// @param action to check
  /// @return ture if action has been *performed* false otherwise
  bool buttonDown(std::string action) const;

  /// @brief checks if the any of the buttons asigned to an action have been
  /// *released* during the frame
  /// @param action to check
  /// @return ture if action has been *performed* false otherwise
  bool buttonUp(std::string action) const;

  /// @brief checks if the any of the buttons asigned to an action is
  /// *currently held down*
  /// @param action to check
  /// @return ture if action is *currently held down* false otherwise
  bool buttonPressed(std::string action) const;

  //TODO: integrate in generic axis system
  float mousePositionX() const;
  float mousePositionY() const;
  

 private:
  struct KeyState {
    bool pushed = false;
    bool pressed = false;
    bool released = false;
  };

  InputManager() = delete;

  static void GenericButtonCallback(int button, int action);
  static void KeyCallback(GLFWwindow* window, int key, int scancode, int action,
                          int mods);
  static void MouseButtonCallback(GLFWwindow* window, int button, int action,
                                  int mods);
  static void ScrollCallback(GLFWwindow* window, double xoffset,
                             double yoffset);
  static void CursorCallback(GLFWwindow* window, double xpos, double ypos);

  // holds the state of the buttons present on map_
  inline static std::unordered_map<InputButton, KeyState> s_mapped_buttons;
  // hold states of the buttons modified in the las frame so that they can be
  // reset at the end of the frame
  inline static std::vector<KeyState*> s_modified_keys;

  //retrieves the states of all the buttons with an action
  std::vector<KeyState> findKeyState(const InputButtonMap& map,
                                     std::string s) const;

  inline static float mouse_x_;
  inline static float mouse_y_;

  InputButtonMap map_;
  GLFWwindow* window_;
};
