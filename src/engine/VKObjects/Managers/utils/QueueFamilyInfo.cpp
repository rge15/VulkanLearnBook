#include "QueueFamilyInfo.hpp"

namespace Graphics::Manager
{
	bool
	QueueFamilyInfo::isComplete() const noexcept
	{
		if( _graphicsFamilyQueueIndex.has_value() && _presentFamilyQueueIndex.has_value() )
			return true;
		return false;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	QueueFamilyInfo::pickBestPhysicalDeviceQueues(
		const std::vector<VkQueueFamilyProperties>& p_queueProp,
		const VkSurfaceKHR& p_surface,
		const VkPhysicalDevice& p_device
	) noexcept
	{
		int i { 0 };

		clean();
		
		for(auto& prop : p_queueProp )
		{
			checkGraphicQueueIndex(	prop, i );

			checkPresentQueueIndex( prop, i, p_surface, p_device);

			if( isComplete() )
				break;
		
			++i;
		}
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	QueueFamilyInfo::getSetIndex(std::set<uint32_t>& p_set) const noexcept
	{
		
		//? Si esto se tiene que ejecutar en cada maquina y esa máquina no soporta Vulkan lo mismo no es buena idea dejar esto en release de vulkan
		ASSERT( _graphicsFamilyQueueIndex.has_value(), "There's no available index queue for graphic support. ;c")
		ASSERT( _presentFamilyQueueIndex.has_value(), "There's no available index queue for present support. ;c")
		
		p_set.insert(_graphicsFamilyQueueIndex.value());
		p_set.insert(_presentFamilyQueueIndex.value());
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	QueueFamilyInfo::checkGraphicQueueIndex(
		const VkQueueFamilyProperties& p_prop,
		const int& p_queueId) noexcept
	{
		if( (p_prop.queueFlags & VK_QUEUE_GRAPHICS_BIT) && !(_graphicsFamilyQueueIndex.has_value()) )
		{
			_graphicsFamilyQueueIndex = p_queueId;
		}
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	QueueFamilyInfo::checkPresentQueueIndex(
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

		if( (present == VK_TRUE) && !(_presentFamilyQueueIndex.has_value()) )
			_presentFamilyQueueIndex = p_queueId;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	QueueFamilyInfo::clean() noexcept
	{
		_graphicsFamilyQueueIndex.reset();
		_presentFamilyQueueIndex.reset();
	}

}