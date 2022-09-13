#include "../utilities/assertMacros.hpp" 
#include "../utilities/config.hpp"
#include "../utilities/graphicsInclude.hpp"

//VK Objects Includes
namespace Graphics
{
	class VDriver
	{

	private:
		uint32_t _width{ 800 }, _height{ 400 };

		// std::unique_ptr<VkInstance> _vkinstance {nullptr};
		VkInstance  _vkinstance {nullptr};

		std::unique_ptr<GLFWwindow, void (*)(GLFWwindow*) > _window { nullptr , nullptr };


	public:
		VDriver(const uint32_t p_w = 640, const uint32_t p_h = 480) noexcept;

		~VDriver();

		void initGLFW() const noexcept;

		void createWindow() noexcept;

		void createVKInstance() noexcept;

		void createVKPhDevice() noexcept;

		static void deleteWindow( GLFWwindow* p_window )
		{
			glfwDestroyWindow( p_window );
			glfwTerminate();
		}

		GLFWwindow*
		getWindow() const noexcept;

	};

}