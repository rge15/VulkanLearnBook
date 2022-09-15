#include "VDriver.hpp"

namespace Graphics
{

	VDriver::VDriver(const uint32_t p_w, const uint32_t p_h) noexcept
	: _width { p_w }, _height { p_h }
	{
		initGLFW();
		createWindow();
		createVKInstance();
		createVKPhDevice();
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	VDriver::~VDriver()
	{
		VkResult result = vkDeviceWaitIdle( _vkDevice );

		ASSERT( result == VK_SUCCESS, "Error waitid DEvices for destruction" )

		vkDestroyDevice(
			_vkDevice,
			nullptr
		);

		vkDestroyInstance(
			_vkInstance,
			nullptr
		);

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

	void 
	VDriver::createVKInstance() noexcept
	{
		VkResult result;
		VkInstanceCreateInfo 	instInfo 	{};
		VkApplicationInfo		appInfo 	{};

		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pNext = {nullptr};
		appInfo.pApplicationName = {"App"};
		appInfo.applicationVersion = 1;
		appInfo.engineVersion = 1;
		appInfo.pEngineName = {"Engine 0.1"};
		appInfo.apiVersion = VK_MAKE_VERSION(1,0,0);

		instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instInfo.pApplicationInfo = &appInfo;
		instInfo.pNext = {nullptr};
		// In next chapters we will learn about these flags
		instInfo.flags = {0};
		instInfo.enabledLayerCount = {0};
		instInfo.ppEnabledLayerNames = {nullptr};
		instInfo.enabledExtensionCount = {0};
		instInfo.ppEnabledExtensionNames = {nullptr};

		result = vkCreateInstance(
			&instInfo,
			nullptr,
			&_vkInstance
		);

		ASSERT( result == VK_SUCCESS, "Errors creating VK Instance ;c")

		if(	result == VK_SUCCESS )
			std::cout << "Bien creada la instancia crack, a ver los device" << std::endl;

	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	VDriver::createVKPhDevice() noexcept
	{

		ASSERT(_vkInstance, "Create a Instance before fetching Physical Devices Sir")

		//Aquí conseguimos todos los physical devices del ordenador
		std::vector<VkPhysicalDevice> vkPhDevices;

		GetPhysicalDevices( _vkInstance, vkPhDevices );
		
		//? Logging Physical Devices Properties & Memories
		Logger::PrintDevicesMemoAndProperties( vkPhDevices );

		VkDeviceCreateInfo deviceInfo{};
		VkPhysicalDeviceFeatures supportedFeatures{}, requiredFeatures{};
		VkDeviceQueueCreateInfo queueInfo{};

		vkGetPhysicalDeviceFeatures(
			vkPhDevices[0],
			&supportedFeatures
		);

		requiredFeatures.multiDrawIndirect = supportedFeatures.multiDrawIndirect;
		requiredFeatures.geometryShader = VK_TRUE;
		requiredFeatures.tessellationShader = VK_TRUE;

		queueInfo.sType = {VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO};
		queueInfo.pNext = {nullptr};
		queueInfo.queueCount = {1};
		queueInfo.flags = {0};
		queueInfo.queueFamilyIndex = {0};
		queueInfo.pQueuePriorities = {nullptr};

		deviceInfo.sType = {VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
		deviceInfo.pNext = {nullptr};
		deviceInfo.flags = {0};
		deviceInfo.enabledLayerCount = {0};
		deviceInfo.enabledExtensionCount = {0};
		deviceInfo.ppEnabledExtensionNames = {nullptr};
		deviceInfo.ppEnabledLayerNames = {nullptr};
		deviceInfo.queueCreateInfoCount = {1};
		deviceInfo.pQueueCreateInfos = {&queueInfo};
		deviceInfo.pEnabledFeatures = {&requiredFeatures};

		auto result = vkCreateDevice(
			vkPhDevices[0],
			&deviceInfo,
			nullptr,
			&_vkDevice
		);

		ASSERT( result == VK_SUCCESS, "Problems creating the logical Device men")

		if(result == VK_SUCCESS)
			std::cout << "Bien creado el Logical device. Well Done." << std::endl;

	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	GLFWwindow*
	VDriver::getWindow() const noexcept
	{
		return _window.get();
	}

}