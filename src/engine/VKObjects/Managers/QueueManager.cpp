#include "QueueManager.hpp"

namespace Graphics::Manager
{

	bool
	QueueManager::checkQueuesSuitability( VkPhysicalDevice& p_device, VkSurfaceKHR& p_surface ) noexcept
	{
		std::vector<VkQueueFamilyProperties> queueProp {};
		getPhysicalDeviceQueueProperties( p_device , queueProp );

		_queueIndexInfo.pickBestPhysicalDeviceQueues(queueProp, p_surface, p_device);

		return _queueIndexInfo.isComplete();
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	QueueManager::initQueueCreateInfo() noexcept
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

	void
	QueueManager::setGraphicHandler( VkDevice& p_device ) noexcept
	{
		vkGetDeviceQueue( p_device, _queueIndexInfo._graphicsFamilyQueueIndex.getValue(), 0, &_graphicsQueueHandler);
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	QueueManager::setPresentHandler( VkDevice& p_device ) noexcept
	{
		vkGetDeviceQueue( p_device, _queueIndexInfo._presentFamilyQueueIndex.getValue(), 0, &_presentQueueHandler);
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	VkQueue&
	QueueManager::getGraphicQueueHandler() noexcept
	{
		return _graphicsQueueHandler;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	VkQueue&
	QueueManager::getPresentQueueHandler() noexcept
	{
		return _presentQueueHandler;
	}


	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	QueueManager::updateQueueIdData() noexcept
	{
		_queueIndexInfo.updateQueueData();
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	int
	QueueManager::getGraphicQueueId() const noexcept
	{ 
		if( _queueIndexInfo._graphicsFamilyQueueIndex.hasValue() )
		{
			return _queueIndexInfo._graphicsFamilyQueueIndex.getValue();
		}
		std::cout << "There isn't graphic queue set yet \n";
		return -1;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	int
	QueueManager::getPresentQueueId() const noexcept
	{ 
		if( _queueIndexInfo._presentFamilyQueueIndex.hasValue() )
		{
			return _queueIndexInfo._presentFamilyQueueIndex.getValue();
		}
		std::cout << "There isn't present queue set yet \n";
		return -1;
	}

}