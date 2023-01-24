#include "DeviceManager.hpp"

namespace Graphics::Manager
{
	Device::Device( Instance& p_vkInstance, GLFWwindow& p_window ) noexcept
	: _engineInstance { p_vkInstance }, _window { p_window }
	{
		getSurfaceDisplay();
		getPhysicalDevice();
		_queueManager.initQueueCreateInfo();
		initFeatureRequeriments();
		initCreationInfo();
		createDevice();
		updateQueueData();
		createSwapchain();
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	Device::~Device() noexcept
	{
		VkResult result = vkDeviceWaitIdle( _device );

		ASSERT( result == VK_SUCCESS, "Error waitid Devices for destruction" )

		_swapchain.DestroySwapchain( _device );

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
		auto queueCheck = _queueManager.checkQueuesSuitability(p_device, _surface);
		if( !queueCheck )
			return false;
		
		auto extensionCheck = checkExtensionsSuitability( p_device );
		if( !extensionCheck )
			return false;

		auto swapchainCheck = _swapchain.checkSuitability( p_device, _surface );
		if( !swapchainCheck )
			return false;
		
		return true;
	}
	
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	bool Device::checkExtensionsSuitability( VkPhysicalDevice& p_device ) noexcept
	{
		std::vector<VkExtensionProperties> extProp {};
		getPhysicalDeviceAvailableExtensions( p_device , extProp );

		std::set<std::string> requiredExt ( _requiredDeviceExtensions.begin(), _requiredDeviceExtensions.end() );

		for(auto& extension : extProp)
		{
			requiredExt.erase( extension.extensionName );
		}

		return requiredExt.empty();
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
		_deviceFeature.geometryShader = deviceFeatures.geometryShader;
		_deviceFeature.tessellationShader = deviceFeatures.tessellationShader;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void Device::initCreationInfo() noexcept
	{
		auto& instanceInfo = _engineInstance.getInstanceInfo();

		_deviceInfo.sType = {VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
		_deviceInfo.pNext = {nullptr};
		_deviceInfo.flags = {0};

		_deviceInfo.enabledExtensionCount = { (uint32_t) _requiredDeviceExtensions.size() };
		_deviceInfo.ppEnabledExtensionNames = { _requiredDeviceExtensions.data() };
		
		_deviceInfo.queueCreateInfoCount = {(uint32_t)_queueManager.getQueueCount()};
		_deviceInfo.pQueueCreateInfos = { _queueManager.getQueueData()};

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

	void Device::updateQueueData() noexcept
	{
		_queueManager.setGraphicHandler( _device );
		_queueManager.setPresentHandler( _device );
		//? If you add a Queue Handler, have to update the updateQueueIdData(); 
		_queueManager.updateQueueIdData();
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

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void Device::createSwapchain() noexcept
	{
		_swapchain.settingUpSwapchain( _window );
		_swapchain.createSwapchain( _device, _surface, _queueManager );
	}

}