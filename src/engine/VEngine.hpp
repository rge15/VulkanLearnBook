#include "../utilities/config.hpp"
#include <GLFW/glfw3.h>

class VEngine
{
private:
	uint32_t _width, _height;

	GLFWwindow* _window {nullptr};

	VkInstance* _vkinstance {nullptr};

public:

	VEngine(const uint32_t p_w = 640, const uint32_t p_h = 480 ) noexcept;

	~VEngine() noexcept;

	void createWindow() noexcept;

	void createVKInstance() noexcept;

};
