#include <optional>
#include <string>



class Window
{
public:

	~Window();
	Window(const Window&) = delete;
	//lvalue move constructor
	Window(Window& w);
	//rvalue move constructor
	Window(Window&& w) noexcept;

	static std::optional<Window> Make(int w, int h, const char* title);

	/// <summary>
	/// checks if the should be closed and refreshes buffer
	/// </summary>
	bool isDone() const;

private:
	Window(int w, int h, const char* title);

	struct GLFWwindow* window_handle_;
};
