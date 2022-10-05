#include <vulkan/vulkan.h>
#include <utilities/config.hpp>
#include "../Managers/utils/QueueFamilyInfo.hpp"

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
	getPhysicalDeviceQueue(
		VkPhysicalDevice& device,
		Manager::QueueFamilyInfo& queue
	) noexcept;

	void
	pickBestPhysicalDeviceQueue(
		const std::vector<VkQueueFamilyProperties>& p_queueProp,
		Manager::QueueFamilyInfo& p_queueIndex
	) noexcept;


}