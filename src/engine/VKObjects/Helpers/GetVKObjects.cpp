#include "GetVKObjects.hpp"

namespace Graphics
{

	void
	GetPhysicalDevices( VkInstance& instance, std::vector<VkPhysicalDevice>& phDevices ) noexcept
	{
		uint32_t devicesCount{0}; 

		vkEnumeratePhysicalDevices(
			instance,
			&devicesCount,
			nullptr
		);

		phDevices.reserve(devicesCount);

		vkEnumeratePhysicalDevices(
			instance,
			&devicesCount,
			&phDevices[0]
		);
	}


}