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
		std::vector<VkPhysicalDevice> devices{};

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
		//TODO : Esto se puede conceptualizar seguro
		std::vector<VkQueueFamilyProperties> queueProp {};
		getPhysicalDeviceQueueProperties( _phDevice , queueProp );

		_queueIndexInfo.pickBestPhysicalDeviceQueues(queueProp, _surface, _phDevice);

		std::set<uint32_t> queueIndex {};
		_queueIndexInfo.getSetIndex(queueIndex);

		_queueInfo.resize( queueIndex.size() );

		int i = 0;
		for(auto queueID : queueIndex)
		{
			_queueInfo[i].sType = {VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO};
			_queueInfo[i].pNext = {nullptr};
			_queueInfo[i].queueCount = {1};
			_queueInfo[i].flags = {0};
			_queueInfo[i].pQueuePriorities = &_queueIndexInfo._priorityValue;
			_queueInfo[i].queueFamilyIndex = queueID;
			++i;
		}
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
		
		_deviceInfo.queueCreateInfoCount = {(uint32_t)_queueInfo.size()};
		_deviceInfo.pQueueCreateInfos = {_queueInfo.data()};

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