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
		//TODO : Hacer la creación de la swapchain
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	Device::~Device() noexcept
	{
		VkResult result = vkDeviceWaitIdle( _device );

		ASSERT( result == VK_SUCCESS, "Error waitid Devices for destruction" )

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

		for( auto& phDevice : devices )
		{
			if (getSuitableDevice( phDevice ))
			{
				_phDevice = phDevice;
				break;
			}
		}
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	
	bool Device::getSuitableDevice( VkPhysicalDevice& p_device ) noexcept
	{
		//TODO : Ahora mismo tengo unas features puestas a piñon, cuando haga falta cambiarlo estaría puta madre la vdd
		// checkFeaturesSuitability( p_device );

		auto queueCheck = checkQueuesSuitability( p_device );
		if( !queueCheck )
			return false;
		
		auto extensionCheck = checkExtensionsSuitability( p_device );
		if( !extensionCheck )
			return false;

		auto swapchainCheck = checkSwapchainSuitability( p_device );
		if( !swapchainCheck )
			return false;
		
		return true;
	}
	
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	bool Device::checkSwapchainSuitability( VkPhysicalDevice& p_device ) noexcept
	{
		SwapchainSupportInfo swapInfo;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR( p_device, _surface, &swapInfo._surfaceCapabilities);
		getPhysicalDeviceSurfaceFormats( p_device, swapInfo._formats, _surface);
		getPhysicalDevicePresentModes( p_device, swapInfo._presentModes, _surface);

		auto availableFormats = !swapInfo._formats.empty();
		auto availablePresentModes = !swapInfo._presentModes.empty();

		return availableFormats && availablePresentModes;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	bool Device::checkExtensionsSuitability( VkPhysicalDevice& p_device ) noexcept
	{
		std::vector<VkExtensionProperties> extProp {};
		getPhysicalDeviceAvailableExtensions( p_device , extProp );

		std::set<std::string> requiredExt ( _requiredDeviceExt.begin(), _requiredDeviceExt.end() );

		for(auto& extension : extProp)
		{
			requiredExt.erase( extension.extensionName );
		}

		return requiredExt.empty();
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	bool Device::checkQueuesSuitability( VkPhysicalDevice& p_device ) noexcept
	{
		std::vector<VkQueueFamilyProperties> queueProp {};
		getPhysicalDeviceQueueProperties( p_device , queueProp );

		_queueIndexInfo.pickBestPhysicalDeviceQueues(queueProp, _surface, p_device);

		return _queueIndexInfo.isComplete();
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

		_deviceInfo.enabledExtensionCount = { (uint32_t) _requiredDeviceExt.size() };
		_deviceInfo.ppEnabledExtensionNames = { _requiredDeviceExt.data() };
		
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
		vkGetDeviceQueue( _device, _queueIndexInfo._graphicsFamilyQueueIndex.value(), 0, &_graphicsQueueHandler);
		// vkGetDeviceQueue( _device, _queueIndexInfo._presentFamilyQueueIndex.value(), 0, &_presentQueueHandler);
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