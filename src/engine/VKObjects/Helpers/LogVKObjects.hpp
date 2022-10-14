#include <vulkan/vulkan.h>
#include "../../../utilities/config.hpp"

namespace Graphics
{
	namespace Logger
	{
		/**
		 * 	@brief Logs the physical device properties 
		 * 
		 * 	@param p_device The Vulkan Physical Device
		*/
		void PrintPhysicalDeviceProperties( VkPhysicalDevice & p_device) noexcept;

		/**
		 * 	@brief Logs the physical device memory properties 
		 * 
		 * 	@param p_device The Vulkan Physical Device
		*/
		void PrintPhysicalDeviceMemoryProperties( VkPhysicalDevice & p_device) noexcept;

		/**
		 * 	@brief Logs the physical device queues attached to the physical device 
		 * 
		 * 	@param p_device The Vulkan Physical Device
		*/
		void PrintPhysicalDeviceQueues( VkPhysicalDevice & p_device) noexcept;
	
		/**
		 * 	@brief Logs the physical device queues, memory and properties
		 * 			attached to each physical device in the passed vector 
		 * 
		 * 	@param p_devices Vector reference to the physical devices to log
		*/
		void PrintDevicesMemoAndProperties( std::vector<VkPhysicalDevice>& p_devices ) noexcept;
	}
}