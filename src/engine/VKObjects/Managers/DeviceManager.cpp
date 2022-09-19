#include "DeviceManager.hpp"

namespace Graphics::Manager
{
	Device::Device( VkInstance& p_vkInstance ) noexcept
	: _engineInstance { p_vkInstance }
	{
		getPhysicalDevice();
		initQueueCreateInfo();
		initFeatureRequeriments();
		initCreationInfo();
		createDevice();
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	Device::~Device() noexcept
	{
		VkResult result = vkDeviceWaitIdle( _device );

		ASSERT( result == VK_SUCCESS, "Error waitid DEvices for destruction" )

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

		GetPhysicalDevices( _engineInstance, devices );

		_phDevice = devices[0];
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
		_queueInfo.sType = {VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO};
		_queueInfo.pNext = {nullptr};
		_queueInfo.queueCount = {1};
		_queueInfo.flags = {0};
		_queueInfo.queueFamilyIndex = {0};
		_queueInfo.pQueuePriorities = {nullptr};
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void Device::initCreationInfo() noexcept
	{
		_deviceInfo.sType = {VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
		_deviceInfo.pNext = {nullptr};
		_deviceInfo.flags = {0};
		_deviceInfo.enabledLayerCount = {0};
		_deviceInfo.enabledExtensionCount = {0};
		_deviceInfo.ppEnabledExtensionNames = {nullptr};
		_deviceInfo.ppEnabledLayerNames = {nullptr};
		_deviceInfo.queueCreateInfoCount = {1};
		_deviceInfo.pQueueCreateInfos = {&_queueInfo};
		_deviceInfo.pEnabledFeatures = {&_deviceFeature};
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

}