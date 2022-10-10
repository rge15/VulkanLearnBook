#include "SwapchainManager.hpp"


namespace Graphics::Manager
{
	void
	SwapchainManager::settingUpSwapchain( GLFWwindow& p_window ) noexcept
	{
		_swapchainInfo.getFinalPresentMode();
		_swapchainInfo.getFinalFormat();
		_swapchainInfo.getFinalExtent( p_window );
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	SwapchainManager::fillSwapchainCreateInfo( 
		VkSurfaceKHR& p_surface,
		QueueManager& p_queues
	) noexcept
	{
		uint32_t imagecount = _swapchainInfo._surfaceCapabilities.minImageCount + 1;
		uint32_t maxImageCount = _swapchainInfo._surfaceCapabilities.maxImageCount;

		if( maxImageCount > 0 && imagecount > maxImageCount )
			imagecount = maxImageCount;

		_swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		_swapchainCreateInfo.pNext = nullptr;
		_swapchainCreateInfo.surface = p_surface;
		_swapchainCreateInfo.imageFormat = _swapchainInfo._finalFormat.format;
		_swapchainCreateInfo.minImageCount = imagecount;
		_swapchainCreateInfo.imageColorSpace = _swapchainInfo._finalFormat.colorSpace;
		_swapchainCreateInfo.imageExtent = _swapchainInfo._swapchainExtent;
		_swapchainCreateInfo.imageArrayLayers = 1;
		_swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		_swapchainCreateInfo.preTransform = _swapchainInfo._surfaceCapabilities.currentTransform;
		_swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		_swapchainCreateInfo.clipped = VK_TRUE;
		_swapchainCreateInfo.presentMode = _swapchainInfo._finalPresentMode;
		_swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

		fillQueueDataCreateInfo( p_queues );
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	SwapchainManager::fillQueueDataCreateInfo( QueueManager& p_queues ) noexcept
	{
		uint32_t graphicQueueId = p_queues.getGraphicQueueId();
		uint32_t presentQueueId = p_queues.getPresentQueueId();

		auto& queueFamily = p_queues.getQueueFamilyInfo();

		if( graphicQueueId == presentQueueId )
		{
			_swapchainCreateInfo.queueFamilyIndexCount = 0;
			_swapchainCreateInfo.pQueueFamilyIndices = nullptr;
			_swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}else
		{
			_swapchainCreateInfo.queueFamilyIndexCount = queueFamily._queuesIds.size();
			_swapchainCreateInfo.pQueueFamilyIndices = queueFamily._queuesIds.data();
			_swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		}
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	SwapchainManager::createSwapchain(
		VkDevice& p_device,
		VkSurfaceKHR& p_surface,
		QueueManager& p_queues
	) noexcept
	{
		fillSwapchainCreateInfo( p_surface, p_queues );

		vkCreateSwapchainKHR( p_device, &_swapchainCreateInfo, nullptr, &_swapchain );

		std::cout << "[INFO] Nice created la swapchain crack \n";

	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	SwapchainManager::DestroySwapchain( VkDevice& p_device ) noexcept
	{
		vkDestroySwapchainKHR( p_device, _swapchain, nullptr);
	}

}