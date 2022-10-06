#pragma once
#include <vulkan/vulkan.h>
#include <utilities/config.hpp>
#include <utilities/assertMacros.hpp>
#include "LogVKObjects.hpp"

namespace Graphics
{
	void
	getPhysicalDevices(
		VkInstance& instance,
		std::vector<VkPhysicalDevice>& phDevices
	) noexcept;

	void
	pickBestPhysicalDevice(
		const std::vector<VkPhysicalDevice>& phDevices,
		VkPhysicalDevice& device
	) noexcept;

	void
	getPhysicalDeviceQueueProperties(
		VkPhysicalDevice& p_device,
		std::vector<VkQueueFamilyProperties>& p_queueProp
	) noexcept;

}