#pragma once
#include <utilities/config.hpp>
#include <utilities/assertMacros.hpp>
#include <vulkan/vulkan.h>

struct SwapchainSupportInfo
{
	VkSurfaceCapabilitiesKHR _surfaceCapabilities;
	std::vector<VkSurfaceFormatKHR> _formats;
	std::vector<VkPresentModeKHR> _presentModes;

	void clean() noexcept;
};