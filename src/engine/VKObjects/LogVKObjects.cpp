#include "LogVKObjects.hpp"

namespace Graphics
{
	namespace Logger
	{	

		void 
		PrintPhysicalDeviceProperties( VkPhysicalDevice& device) noexcept
		{
			VkPhysicalDeviceProperties vkPhDeviceProp;

			vkGetPhysicalDeviceProperties(
				device,
				&vkPhDeviceProp
			);

			std::cout << "Device Name    : " << vkPhDeviceProp.deviceName << std::endl;
			std::cout << "Device Type    : " << vkPhDeviceProp.deviceType << std::endl;
			std::cout << "Device ID      : " << vkPhDeviceProp.deviceID << std::endl;
			std::cout << "Device Vendor  : " << vkPhDeviceProp.vendorID << std::endl;
			std::cout << "Device API Ver : " << vkPhDeviceProp.apiVersion << std::endl;
		}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

		void 
		PrintPhysicalDeviceMemoryProperties( VkPhysicalDevice& device) noexcept
		{
			VkPhysicalDeviceMemoryProperties vkPhDeviceMem;

			vkGetPhysicalDeviceMemoryProperties(
				device,
				&vkPhDeviceMem
			);

			std::cout << "Device Total Types  : " << vkPhDeviceMem.memoryTypeCount << std::endl;
			
			for(auto& heap : vkPhDeviceMem.memoryTypes)
			{
				std::cout << "------------------------------------------------------------" << std::endl;
				std::cout << "Memory Heap ID          : " << heap.heapIndex << std::endl;
				std::cout << "Memory Heap Properties  : " << heap.propertyFlags << std::endl;
			}
			std::cout << "------------------------------------------------------------" << std::endl;

			std::cout << "Device Total Memory Heaps : " << vkPhDeviceMem.memoryHeapCount << std::endl;

			for(auto& heap : vkPhDeviceMem.memoryHeaps)
			{
				std::cout << "------------------------------------------------------------" << std::endl;
				std::cout << "Memory Heap Size  : " << heap.size << std::endl;
				std::cout << "Memory Heap Flags : " << heap.flags << std::endl;
			}
			std::cout << "------------------------------------------------------------" << std::endl;

		}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

		void 
		PrintPhysicalDeviceQueues( VkPhysicalDevice& device) noexcept
		{
			uint32_t countQueues {0};
			std::vector<VkQueueFamilyProperties> deviceQueue;

			vkGetPhysicalDeviceQueueFamilyProperties(
				device,
				&countQueues,
				nullptr
			);

			deviceQueue.resize(countQueues);

			vkGetPhysicalDeviceQueueFamilyProperties(
				device,
				&countQueues,
				&deviceQueue[0]
			);

			for(auto& queue : deviceQueue)
			{
				std::cout << "------------------------------------------------------------" << std::endl;
				std::cout << "Queue Count     : " << queue.queueCount << std::endl;
				std::cout << "Queue Flags     : " << queue.queueFlags << std::endl;
				std::cout << "Queue Timestamp : " << queue.timestampValidBits << std::endl;
			}

		}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

		void
		PrintDevicesMemoAndProperties( std::vector<VkPhysicalDevice>& devices ) noexcept
		{
			for(auto& device : devices)
			{		
				PrintPhysicalDeviceProperties(device);
				PrintPhysicalDeviceMemoryProperties(device);
				PrintPhysicalDeviceQueues(device);
			}
		}

	}
}