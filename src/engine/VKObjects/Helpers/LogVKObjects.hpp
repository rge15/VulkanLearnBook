#include <vulkan/vulkan.h>
#include "../../../utilities/config.hpp"

namespace Graphics
{
	namespace Logger
	{
		void PrintPhysicalDeviceProperties( VkPhysicalDevice & device) noexcept;

		void PrintPhysicalDeviceMemoryProperties( VkPhysicalDevice & device) noexcept;

		void PrintPhysicalDeviceQueues( VkPhysicalDevice & device) noexcept;
	
		void PrintDevicesMemoAndProperties( std::vector<VkPhysicalDevice>& devices ) noexcept;
	}
}