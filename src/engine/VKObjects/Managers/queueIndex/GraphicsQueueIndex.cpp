#include "GraphicsQueueIndex.hpp"

namespace Graphics::Manager
{
	void
	GraphicsQueueIndex::checkQueueGraphicsProperties(
		const VkQueueFamilyProperties& p_prop,
		const int& p_queueId
	) noexcept
	{
		if( (p_prop.queueFlags & VK_QUEUE_GRAPHICS_BIT) && !( _queueId.has_value()) )
		{
			_queueId = p_queueId;
		}
	}

}