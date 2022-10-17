#include "QueueFamilyInfo.hpp"

namespace Graphics::Manager
{
	bool
	QueueFamilyInfo::isComplete() const noexcept
	{
		if( _graphicsFamilyQueueIndex.hasValue() && _presentFamilyQueueIndex.hasValue() )
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
			checkAllQueueManagers( prop, i, p_surface, p_device );

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
		ASSERT( _graphicsFamilyQueueIndex.hasValue(), "There's no available index queue for graphic support. ;c")
		ASSERT( _presentFamilyQueueIndex.hasValue(), "There's no available index queue for present support. ;c")
		
		p_set.insert(_graphicsFamilyQueueIndex.getValue());
		p_set.insert(_presentFamilyQueueIndex.getValue());
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	QueueFamilyInfo::checkAllQueueManagers(
		const VkQueueFamilyProperties& p_prop,
		const int& p_queueId,
		const VkSurfaceKHR& p_surface,
		const VkPhysicalDevice& p_device
	) noexcept
	{
		_graphicsFamilyQueueIndex.checkQueueGraphicsProperties( p_prop, p_queueId );

		_presentFamilyQueueIndex.checkQueuePresentProperties(
			p_prop, p_queueId, p_surface, p_device
		);
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	QueueFamilyInfo::clean() noexcept
	{
		_graphicsFamilyQueueIndex.reset();
		_presentFamilyQueueIndex.reset();
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	QueueFamilyInfo::updateQueueData() noexcept
	{
		_queuesIds.clear();
		_queuesIds.shrink_to_fit();

		_queuesIds.push_back( _presentFamilyQueueIndex.getValue() );
		_queuesIds.push_back( _graphicsFamilyQueueIndex.getValue() );

	}


}