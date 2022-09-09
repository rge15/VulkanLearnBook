#include "VEngine.hpp"

//TODO : A ver crack, antes de ponerte a seguir con los videos mira bien que es una instance
//TODO : de vulkan y una vez lo sepas intenta estructurar un poco el código. Esto pa mañana <3 

VEngine::VEngine(const uint32_t p_w, const uint32_t p_h ) noexcept
: _width { p_w }, _height { p_h }
{
	createWindow();
	createVKInstance();
}

VEngine::~VEngine() noexcept
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void 
VEngine::createWindow() noexcept
{
	glfwInit();

	glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
	glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );

	_window = glfwCreateWindow( _width, _height, "VulkanEngine", nullptr, nullptr);

	if( _window )
		std::cout << "Window created succesfully" << std::endl;
	else
		std::cout << "Window creation failed" << std::endl;
}

void 
VEngine::createVKInstance() noexcept
{

}

