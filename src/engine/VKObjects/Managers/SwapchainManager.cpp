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

		getImages( p_device );

		getImageViews( p_device );
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	SwapchainManager::DestroySwapchain( VkDevice& p_device ) noexcept
	{
		for(auto& imgView : _swapchainImageViews )
			vkDestroyImageView( p_device, imgView, nullptr );

		vkDestroySwapchainKHR( p_device, _swapchain, nullptr);
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	SwapchainManager::getImages( VkDevice& p_device ) noexcept
	{
		uint32_t imageCount {0};

		vkGetSwapchainImagesKHR( p_device, _swapchain, &imageCount, nullptr);

		_swapchainImages.resize(imageCount);

		vkGetSwapchainImagesKHR( p_device, _swapchain, &imageCount, _swapchainImages.data());

		std::cout << "[INFO] Getting "<< imageCount << " images from the swapchain \n";
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	SwapchainManager::getImageViews( VkDevice& p_device ) noexcept
	{
		std::size_t imageNumbers = _swapchainImages.size();
		VkImageViewCreateInfo _viewInfo {};
		VkResult result {};
		std::size_t i { 0 };
		
		_swapchainImageViews.resize(imageNumbers);

		_viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		_viewInfo.format = _swapchainInfo._finalFormat.format;
		_viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		_viewInfo.pNext = nullptr;
		_viewInfo.flags = 0;

		_viewInfo.components.r = VK_COMPONENT_SWIZZLE_R;
		_viewInfo.components.b = VK_COMPONENT_SWIZZLE_B;
		_viewInfo.components.g = VK_COMPONENT_SWIZZLE_G;
		_viewInfo.components.a = VK_COMPONENT_SWIZZLE_A;

		_viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		_viewInfo.subresourceRange.baseArrayLayer = 0;
		_viewInfo.subresourceRange.baseMipLevel = 0;
		_viewInfo.subresourceRange.layerCount = 1;
		_viewInfo.subresourceRange.levelCount = 1;

		for(auto& image : _swapchainImages)
		{
			_viewInfo.image = image;
			vkCreateImageView( p_device, &_viewInfo, nullptr, &_swapchainImageViews[i++] );
			ASSERT(result == VK_SUCCESS, "Error creating ImageView of swapchain")
		}

	}


}