#pragma once
#include <vulkan/vulkan.h>
#include <utilities/config.hpp>
#include <utilities/assertMacros.hpp>
#include "LogVKObjects.hpp"

namespace Graphics
{
	/**
	 * 	@brief Gets the physical devices that suports the given Vulkan Instance
	 * 
	 * 	@param p_instance The Vulkan Instance
	 * 	@param p_phDevices Vector Reference to place the physcial devices into 
	*/
	void
	getPhysicalDevices(
		VkInstance& p_instance,
		std::vector<VkPhysicalDevice>& p_phDevices
	) noexcept;

	/**
	 * 	@brief Gets the queue family properties that suports the given Vulkan Physical Device
	 * 
	 * 	@param p_device The Vulkan Physical Device
	 * 	@param p_phDevices Vector Reference to place the queue family properties into 
	*/
	void
	getPhysicalDeviceQueueProperties(
		VkPhysicalDevice& p_device,
		std::vector<VkQueueFamilyProperties>& p_queueProp
	) noexcept;

	/**
	 * 	@brief Gets the available extensions that suports the given Vulkan Physical Device
	 * 
	 * 	@param p_device The Vulkan Physical Device
	 * 	@param p_phDevices Vector Reference to place the queue extensions properties into 
	*/
	void
	getPhysicalDeviceAvailableExtensions(
		VkPhysicalDevice& _phDevice ,
		std::vector<VkExtensionProperties>& p_extProp
	) noexcept;

	/**
	 * 	@brief Gets the surface formats that suports the 
	 * 			given Vulkan Physical Device and the Vulkan surface
	 * 
	 * 	@param p_device The Vulkan Physical Device
	 * 	@param p_phDevices Vector Reference to place the surface properties into 
	 * 	@param p_surface The Vulkan Surface
	*/
	void
	getPhysicalDeviceSurfaceFormats( 
		VkPhysicalDevice& p_device,
		std::vector<VkSurfaceFormatKHR>& p_surfaceFormats,
		VkSurfaceKHR& p_surface
	) noexcept;

	/**
	 * 	@brief Gets the present modes that suports the 
	 * 			given Vulkan Physical Device and the Vulkan surface
	 * 
	 * 	@param p_device The Vulkan Physical Device
	 * 	@param p_phDevices Vector Reference to place the present modes into 
	 * 	@param p_surface The Vulkan Surface
	*/
	void
	getPhysicalDevicePresentModes(
		VkPhysicalDevice& p_device,
		std::vector<VkPresentModeKHR>& p_presentModes,
		VkSurfaceKHR& p_surface
	) noexcept;

}