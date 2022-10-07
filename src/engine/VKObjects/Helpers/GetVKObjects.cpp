#include "GetVKObjects.hpp"

namespace Graphics
{

	void
	getPhysicalDevices( VkInstance& p_instance, std::vector<VkPhysicalDevice>& p_phDevices ) noexcept
	{
		uint32_t devicesCount{0}; 

		vkEnumeratePhysicalDevices(
			p_instance,
			&devicesCount,
			nullptr
		);

		ASSERT( (devicesCount > 0), "There's no available physical devices for the vulkan app." );

		p_phDevices.resize(devicesCount);

		vkEnumeratePhysicalDevices(
			p_instance,
			&devicesCount,
			p_phDevices.data()
		);

	}

	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------

	void
	getPhysicalDeviceQueueProperties(
		VkPhysicalDevice& p_device,
		std::vector<VkQueueFamilyProperties>& p_queueProp
	) noexcept
	{
		uint32_t queueCount { 0 };

		vkGetPhysicalDeviceQueueFamilyProperties( p_device, &queueCount, nullptr);

		p_queueProp.resize(queueCount);

		vkGetPhysicalDeviceQueueFamilyProperties( p_device, &queueCount, p_queueProp.data());
	}

	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------

	void
	getPhysicalDeviceAvailableExtensions( 
		VkPhysicalDevice& p_device ,
		std::vector<VkExtensionProperties>& p_extProp
	) noexcept
	{
		uint32_t extCount { 0 };

		vkEnumerateDeviceExtensionProperties( p_device, nullptr, &extCount, nullptr);

		p_extProp.resize(extCount);

		vkEnumerateDeviceExtensionProperties( p_device, nullptr, &extCount, p_extProp.data());	
	}

	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------

	void
	getPhysicalDeviceSurfaceFormats( 
		VkPhysicalDevice& p_device,
		std::vector<VkSurfaceFormatKHR>& p_surfaceFormats,
		VkSurfaceKHR& p_surface
	) noexcept
	{
		uint32_t formatsCount { 0 };

		vkGetPhysicalDeviceSurfaceFormatsKHR( p_device, p_surface, &formatsCount, nullptr );

		p_surfaceFormats.resize(formatsCount);

		vkGetPhysicalDeviceSurfaceFormatsKHR( p_device, p_surface, &formatsCount, p_surfaceFormats.data() );
	}

	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------

	void
	getPhysicalDevicePresentModes(
		VkPhysicalDevice& p_device,
		std::vector<VkPresentModeKHR>& p_presentModes,
		VkSurfaceKHR& p_surface
	) noexcept
	{
		uint32_t modesCount { 0 };

		vkGetPhysicalDeviceSurfacePresentModesKHR( p_device, p_surface, &modesCount, nullptr );

		p_presentModes.resize(modesCount);

		vkGetPhysicalDeviceSurfacePresentModesKHR( p_device, p_surface, &modesCount, p_presentModes.data() );
	}

}