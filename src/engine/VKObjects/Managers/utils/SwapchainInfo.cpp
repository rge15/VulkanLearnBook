#include "SwapchainInfo.hpp"

namespace Graphics::Manager
{

	void
	SwapchainInfo::cleanSupportInfo() noexcept
	{
		_formats.clear();
		_formats.shrink_to_fit();
		_presentModes.clear();
		_presentModes.shrink_to_fit();
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------


	bool
	SwapchainInfo::checkSuitableDevice( VkPhysicalDevice& p_phDevice, VkSurfaceKHR& p_surface ) noexcept
	{
		cleanSupportInfo();

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR( p_phDevice, p_surface, &_surfaceCapabilities);
		getPhysicalDeviceSurfaceFormats( p_phDevice, _formats, p_surface);
		getPhysicalDevicePresentModes( p_phDevice, _presentModes, p_surface);

		auto availableFormats = !_formats.empty();
		auto availablePresentModes = !_presentModes.empty();

		return availableFormats && availablePresentModes;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	SwapchainInfo::getFinalFormat() noexcept
	{
		for(const auto& availableFormat : _formats )
		{
			if( availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
				availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR )
			{
				_finalFormat = availableFormat;
				return;
			}
		}

		std::cout << "[INFO] There's no available format with the specified requirments\n";
		_finalFormat = _formats[0];
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	SwapchainInfo::getFinalPresentMode() noexcept
	{
		for(const auto& mode : _presentModes)
		{
			if( mode == VK_PRESENT_MODE_MAILBOX_KHR )
			{
				_finalPresentMode = mode;
				return;
			}
		}

		std::cout << "[INFO] There's no available present mode with the specified requirments. Setting to FIFO Mode\n";
		_finalPresentMode = VK_PRESENT_MODE_FIFO_KHR;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	SwapchainInfo::getFinalExtent(  GLFWwindow& p_window ) noexcept
	{
		if( _surfaceCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max() )
		{
			_swapchainExtent = _surfaceCapabilities.currentExtent;
			return;
		}
	
		int width { 0 }, height { 0 };
		glfwGetFramebufferSize(&p_window, &width, &height);
	
		_swapchainExtent.width = (uint32_t) width;
		_swapchainExtent.height = (uint32_t) height;
	
		_swapchainExtent.width = std::clamp( 
			_swapchainExtent.width, 
			_surfaceCapabilities.minImageExtent.width,
			_surfaceCapabilities.maxImageExtent.width );
	
		_swapchainExtent.height = std::clamp( 
			_swapchainExtent.height, 
			_surfaceCapabilities.minImageExtent.height,
			_surfaceCapabilities.maxImageExtent.height );
	}

}