#include "VDriver.hpp"

namespace Graphics
{

	VDriver::VDriver(const uint32_t p_w, const uint32_t p_h) noexcept
	: _width { p_w }, _height { p_h }
	{
		initGLFW();
		createWindow();
	
		_vkInstanceManager = std::make_unique<Instance>();
		_vkDeviceManager = std::make_unique<Device>( *_vkInstanceManager.get() );

	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	VDriver::~VDriver()
	{
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	VDriver::initGLFW() const noexcept
	{
		glfwInit();
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	VDriver::createWindow() noexcept
	{
		glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
		glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );

		std::unique_ptr<GLFWwindow, void (*)(GLFWwindow*)> window { 
			glfwCreateWindow( _width, _height, "VulkanEngine", nullptr, nullptr),
			deleteWindow };

		ASSERT(window.get(), "Window creation failed")

		if( window.get() )
			std::cout << "Window created succesfully" << std::endl;
		else
			std::cout << "Window creation failed" << std::endl;

		_window = std::move(window);
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	GLFWwindow*
	VDriver::getWindow() const noexcept
	{
		return _window.get();
	}

}