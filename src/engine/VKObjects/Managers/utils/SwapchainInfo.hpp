#pragma once
#include <utilities/config.hpp>
#include <utilities/assertMacros.hpp>
#include <vulkan/vulkan.h>
#include <engine/VKObjects/Helpers/GetVKObjects.hpp>
#include <utilities/graphicsInclude.hpp>

namespace Graphics::Manager
{
	struct SwapchainInfo
	{
		VkSurfaceCapabilitiesKHR _surfaceCapabilities	{};
		std::vector<VkSurfaceFormatKHR> _formats		{};
		std::vector<VkPresentModeKHR> _presentModes		{};

		VkSurfaceFormatKHR 	_finalFormat		{};
		VkPresentModeKHR	_finalPresentMode	{};
		VkExtent2D			_swapchainExtent	{};


		VkSwapchainKHR _swapchain { VK_NULL_HANDLE };

		void
		cleanSupportInfo() noexcept;

		bool
		checkSuitableDevice( VkPhysicalDevice& p_phDevice, VkSurfaceKHR& p_surface ) noexcept;

		void
		getFinalFormat() noexcept;

		void
		getFinalPresentMode() noexcept;

		void
		getFinalExtent( GLFWwindow& p_window ) noexcept;

	};
}