#include "DeviceManager.hpp"

namespace Graphics::Manager
{
	Device::Device( Instance& p_vkInstance, GLFWwindow& p_window ) noexcept
	: _engineInstance { p_vkInstance }, _window { p_window }
	{
		getSurfaceDisplay();
		getPhysicalDevice();
		initQueueCreateInfo();
		initFeatureRequeriments();
		initCreationInfo();
		createDevice();
		getQueueHandler();
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	Device::~Device() noexcept
	{
		VkResult result = vkDeviceWaitIdle( _device );

		ASSERT( result == VK_SUCCESS, "Error waitid DEvices for destruction" )

		vkDestroySurfaceKHR(
			_engineInstance.getInstance(),
			_surface,
			nullptr
		);

		vkDestroyDevice(
			_device,
			nullptr
		);
	
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void Device::getPhysicalDevice() noexcept
	{
		std::vector<VkPhysicalDevice> devices;

		getPhysicalDevices( _engineInstance.getInstance(), devices );

		pickBestPhysicalDevice( devices, _phDevice);
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void Device::initFeatureRequeriments() noexcept
	{
		VkPhysicalDeviceFeatures deviceFeatures{};

		vkGetPhysicalDeviceFeatures(
			_phDevice,
			&deviceFeatures
		);

		_deviceFeature.multiDrawIndirect = deviceFeatures.multiDrawIndirect;
		_deviceFeature.geometryShader = VK_TRUE;
		_deviceFeature.tessellationShader = VK_TRUE;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void Device::initQueueCreateInfo() noexcept
	{
		getPhysicalDeviceQueue(_phDevice, _queueIndexInfo);

		_queueIndexInfo._priorityValue = 1.0f;

		if( _queueIndexInfo.isComplete() )
			_queueInfo.queueFamilyIndex = _queueIndexInfo._graphicsFamilyQueueIndex.value();
		else
		{
			std::cout << "Non graphical queue found in the physical Device selected." << std::endl;
			_queueInfo.queueFamilyIndex = 0;
		}

		_queueInfo.sType = {VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO};
		_queueInfo.pNext = {nullptr};
		_queueInfo.queueCount = {1};
		_queueInfo.flags = {0};
		_queueInfo.pQueuePriorities = &_queueIndexInfo._priorityValue;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void Device::initCreationInfo() noexcept
	{
		auto& instanceInfo = _engineInstance.getInstanceInfo();

		_deviceInfo.sType = {VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
		_deviceInfo.pNext = {nullptr};
		_deviceInfo.flags = {0};
		_deviceInfo.enabledExtensionCount = {0};
		_deviceInfo.ppEnabledExtensionNames = {nullptr};
		_deviceInfo.queueCreateInfoCount = {1};
		_deviceInfo.pQueueCreateInfos = {&_queueInfo};
		_deviceInfo.pEnabledFeatures = {&_deviceFeature};
		_deviceInfo.enabledLayerCount = instanceInfo.enabledLayerCount;
		_deviceInfo.ppEnabledLayerNames = instanceInfo.ppEnabledLayerNames;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void Device::createDevice() noexcept
	{
		VkResult result = vkCreateDevice(
			_phDevice, &_deviceInfo, nullptr, &_device
		);

		ASSERT( result == VK_SUCCESS, "Problems creating the logical Device men")

		if(result == VK_SUCCESS)
			std::cout << "Bien creado el Logical device. Well Done." << std::endl;

	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void Device::getQueueHandler() noexcept
	{
		vkGetDeviceQueue( _device, _queueIndexInfo._graphicsFamilyQueueIndex.value(), 0, &_queueHandler);
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void Device::getSurfaceDisplay() noexcept
	{
		auto result = glfwCreateWindowSurface( 
			_engineInstance.getInstance(),
			&_window,
			nullptr,
			&_surface
		);

		ASSERT(result == VK_FALSE, " Error creating the surface for display ")
	}
}