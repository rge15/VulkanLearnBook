#include "../utilities/assertMacros.hpp" 
#include "../utilities/config.hpp"
#include "../utilities/graphicsInclude.hpp"
#include "VKObjects/Helpers/LogVKObjects.hpp"
#include "VKObjects/Helpers/GetVKObjects.hpp"
#include "VKObjects/Managers/DeviceManager.hpp"
#include "VKObjects/Managers/InstanceManager.hpp"

//VK Objects Includes
namespace Graphics
{
	class VDriver
	{

	private:
	
		//Using's for legibility
		using Instance = Manager::Instance;
		using Device = Manager::Device;
	
		//Width and heigth for the screen size
		uint32_t _width{ 800 }, _height{ 400 };

		//UniquePtr for managing the Vulkan Instantce and physicalDevice
		std::unique_ptr<Instance> _vkInstanceManager { std::make_unique<Instance>() };
		std::unique_ptr<Device> _vkDeviceManager { std::make_unique<Device>( _vkInstanceManager->getInstance() ) };

		//GLFWWindow uniqPtr handler pre-initialized
		std::unique_ptr<GLFWwindow, void (*)(GLFWwindow*) > _window { nullptr , nullptr };

	public:

		/**
		 * 	@brief Default constructor for the driver manager
		 * 
		 * 	@param p_w Width for the screen size. Default = 640
		 * 	@param p_h Height for the screen size. Default = 640
		*/
		VDriver(const uint32_t p_w = 640, const uint32_t p_h = 480) noexcept;

		/**
		 * 	@brief 	Default destructor for the driver manager.
		 * 			It destroys the Vulkan Device and the Vulkan Instance 
		*/
		~VDriver();

		/**
		 * 	@brief Static Method for handle the GLFWwindow destruction
		 * 			and the glfw terminate
		*/
		static void deleteWindow( GLFWwindow* p_window )
		{
			glfwDestroyWindow( p_window );
			glfwTerminate();
		}

		/**
		 * 	@brief Get the window created by the Engine
		 * 
		 * 	@return Reference to the created window
		*/
		GLFWwindow*
		getWindow() const noexcept;

	private:
		
		/**
		 *	@brief Initializes GLFW window manager 
		*/
		void initGLFW() const noexcept;

		/**
		 * 	@brief 	Method that creates the GLFWWindow
		 * 			Initializes the window uniqPtr 
		 * 			handler of the Instance of the VDriver,
		 *  		and assignated the static destructor deleteWindow.
		*/
		void createWindow() noexcept;

	};

}