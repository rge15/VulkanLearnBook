#pragma once
#include <vulkan/vulkan.h>
#include <utilities/config.hpp>
#include <utilities/assertMacros.hpp>
#include "LogVKObjects.hpp"

namespace Graphics
{
	void
	getPhysicalDevices(
		VkInstance& p_instance,
		std::vector<VkPhysicalDevice>& p_phDevices
	) noexcept;

	void
	getPhysicalDeviceQueueProperties(
		VkPhysicalDevice& p_device,
		std::vector<VkQueueFamilyProperties>& p_queueProp
	) noexcept;

	void
	getPhysicalDeviceAvailableExtensions(
		VkPhysicalDevice& _phDevice ,
		std::vector<VkExtensionProperties>& p_extProp
	) noexcept;

	void
	getPhysicalDeviceSurfaceFormats( 
		VkPhysicalDevice& p_device,
		std::vector<VkSurfaceFormatKHR>& p_surfaceFormats,
		VkSurfaceKHR& p_surface
	) noexcept;

	void
	getPhysicalDevicePresentModes(
		VkPhysicalDevice& p_device,
		std::vector<VkPresentModeKHR>& p_presentModes,
		VkSurfaceKHR& p_surface
	) noexcept;

}