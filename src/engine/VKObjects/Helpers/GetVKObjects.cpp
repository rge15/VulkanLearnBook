#include "GetVKObjects.hpp"

namespace Graphics
{

	void
	getPhysicalDevices( VkInstance& p_instance, std::vector<VkPhysicalDevice>& p_phDevices ) noexcept
	{
		uint32_t devicesCount{0}; 

		vkEnumeratePhysicalDevices(
			p_instance,
			&devicesCount,
			nullptr
		);

		ASSERT( (devicesCount > 0), "There's no available physical devices for the vulkan app." );

		p_phDevices.resize(devicesCount);

		vkEnumeratePhysicalDevices(
			p_instance,
			&devicesCount,
			p_phDevices.data()
		);

	}

	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------

	void
	pickBestPhysicalDevice(const std::vector<VkPhysicalDevice>& p_phDevices, VkPhysicalDevice& p_device) noexcept
	{
		p_device = p_phDevices[0];
	}

	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------

	void
	getPhysicalDeviceQueueProperties( VkPhysicalDevice& p_device, std::vector<VkQueueFamilyProperties>& p_queueProp ) noexcept
	{
		uint32_t queueCount { 0 };

		vkGetPhysicalDeviceQueueFamilyProperties( p_device, &queueCount, nullptr);

		p_queueProp.resize(queueCount);

		vkGetPhysicalDeviceQueueFamilyProperties( p_device, &queueCount, p_queueProp.data());
	}

	
}