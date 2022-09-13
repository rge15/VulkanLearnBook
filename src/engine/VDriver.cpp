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

VDriver::~VDriver()
{
}

void
VDriver::initGLFW() const noexcept
{
	glfwInit();
}

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
		&_vkinstance
	);

	ASSERT( result == VK_SUCCESS, "Errors creating VK Instance ;c")

	if(	result == VK_SUCCESS )
		std::cout << "Bien creada la instancia crack, a ver los device" << std::endl;

}

void
VDriver::createVKPhDevice() noexcept
{

	ASSERT(_vkinstance, "Create a Instance before fetching Physical Devices Sir")
	uint32_t devicesCount {0};
	std::vector<VkPhysicalDevice> vkPhDevice;
	VkPhysicalDeviceProperties vkPhDeviceProp;

	vkEnumeratePhysicalDevices(
		_vkinstance,
		&devicesCount,
		nullptr
	);

	vkPhDevice.resize(devicesCount);

	vkEnumeratePhysicalDevices(
		_vkinstance,
		&devicesCount,
		&vkPhDevice[0]
	);

	std::cout << "Let's Checkear los physical Devices todo wapos" << std::endl;

	for(auto& device : vkPhDevice)
	{
		vkGetPhysicalDeviceProperties(
			device,
			&vkPhDeviceProp
		);
		std::cout << "---------------------------------------------" << std::endl;
		std::cout << "Device Name 	: " << vkPhDeviceProp.deviceName << std::endl;
		std::cout << "Device Type 	: " << vkPhDeviceProp.deviceType << std::endl;
		std::cout << "Device ID My buenas	: " << vkPhDeviceProp.deviceID << std::endl;
		std::cout << "Device Vendor : " << vkPhDeviceProp.vendorID << std::endl;
		std::cout << "Device API Ver: " << vkPhDeviceProp.apiVersion << std::endl;
	}
	std::cout << "---------------------------------------------" << std::endl;

}

GLFWwindow*
VDriver::getWindow() const noexcept
{
	return _window.get();
}

}