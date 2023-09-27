#include <optional>
#include <string>



class Window
{
public:
	static std::optional<Window> Make(int w, int h, const char* title);
	~Window();
	Window(Window&& w);

	bool isDone() const;


private:
	Window(int w, int h, const char* title);

	

	struct GLFWwindow* window;
};
