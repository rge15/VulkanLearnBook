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

		p_phDevices.reserve(devicesCount);

		vkEnumeratePhysicalDevices(
			p_instance,
			&devicesCount,
			&p_phDevices[0]
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
	getPhysicalDeviceQueue( VkPhysicalDevice& p_device, Manager::QueueFamilyInfo& p_queueIndex ) noexcept
	{
		uint32_t queueCount {};

		vkGetPhysicalDeviceQueueFamilyProperties( p_device, &queueCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueProperties(queueCount);

		vkGetPhysicalDeviceQueueFamilyProperties( p_device, &queueCount, queueProperties.data());

		pickBestPhysicalDeviceQueue( queueProperties, p_queueIndex);
	}

	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------

	void
	pickBestPhysicalDeviceQueue(
		const std::vector<VkQueueFamilyProperties>& p_queueProp,
		Manager::QueueFamilyInfo& p_queueIndex
	) noexcept
	{
		int i { 0 };
		for(auto& prop : p_queueProp )
		{
			if( prop.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				p_queueIndex._graphicsFamilyQueueIndex = i;
		
			if( p_queueIndex.isComplete() )
				break;
		
			++i;
		}
	}

}