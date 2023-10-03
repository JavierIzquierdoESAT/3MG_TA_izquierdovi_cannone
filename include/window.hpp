#include "../src/stdafx.hpp"

struct GLFWwindow;

/** Handles Window */
class Window
{
 public:
	//copy constructor
	Window(const Window&) = delete;
	//lvalue move constructor
	Window(Window& w);
	//rvalue move constructor
	Window(Window&& w) noexcept;

	~Window();

	/** creates the window */
	static std::optional<Window> Make(int w, int h, const char* title);

	/** checks if the should be closed and refreshes buffer */
	bool isDone() const;

 private:

	Window(GLFWwindow* w);

	/** openGL window handle */
	GLFWwindow* window_handle_;

};
