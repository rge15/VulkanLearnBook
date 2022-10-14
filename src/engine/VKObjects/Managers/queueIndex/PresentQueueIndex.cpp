#include "PresentQueueIndex.hpp"

namespace Graphics::Manager
{
	void
	PresentQueueIndex::checkQueuePresentProperties(
		const VkQueueFamilyProperties& p_prop,
		const int& p_queueId,
		const VkSurfaceKHR& p_surface,
		const VkPhysicalDevice& p_device
	) noexcept
	{
		VkBool32 present = VK_FALSE;

		vkGetPhysicalDeviceSurfaceSupportKHR(
			p_device, p_queueId, p_surface, &present
		);

		if( (present == VK_TRUE) && !(_queueId.has_value()) )
			_queueId = p_queueId;
	}

}