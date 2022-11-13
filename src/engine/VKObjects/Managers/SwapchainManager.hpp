#pragma once
#include <utilities/config.hpp>
#include <vulkan/vulkan.h>
#include "utils/SwapchainInfo.hpp"
#include "QueueManager.hpp"

namespace Graphics::Manager
{
	class SwapchainManager
	{
		private:
			VkSwapchainKHR _swapchain { VK_NULL_HANDLE };
			SwapchainInfo _swapchainInfo {};
			VkSwapchainCreateInfoKHR _swapchainCreateInfo {};			
			std::vector<VkImage> _swapchainImages {};
			std::vector<VkImageView> _swapchainImageViews {};

			void
			fillSwapchainCreateInfo( VkSurfaceKHR& p_surface, QueueManager& p_queues ) noexcept;

			void
			fillQueueDataCreateInfo( QueueManager& p_queues ) noexcept;

			void
			getImages( VkDevice& p_device ) noexcept;

			void
			getImageViews( VkDevice& p_device ) noexcept;

		public:
			SwapchainManager() noexcept = default;
			~SwapchainManager() noexcept = default;

			void
			DestroySwapchain( VkDevice& p_device ) noexcept;

			bool
			checkSuitability( VkPhysicalDevice& p_phDevice, VkSurfaceKHR& p_surface ) noexcept
			{
				return _swapchainInfo.checkSuitableDevice(p_phDevice, p_surface);
			}

			void
			settingUpSwapchain( GLFWwindow& p_window ) noexcept;

			void
			createSwapchain( VkDevice& p_device, VkSurfaceKHR& p_surface, QueueManager& p_queues ) noexcept;

			const SwapchainInfo&
			getSwapchainInfo() const noexcept { return _swapchainInfo; }

	};
}