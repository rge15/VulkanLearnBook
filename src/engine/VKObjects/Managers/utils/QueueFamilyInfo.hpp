#pragma once
#include <utilities/config.hpp>
#include <utilities/assertMacros.hpp>
#include <vulkan/vulkan.h>

namespace Graphics::Manager
{
	struct QueueFamilyInfo{
		std::optional<uint32_t> _graphicsFamilyQueueIndex;
		std::optional<uint32_t> _presentFamilyQueueIndex;
		float _priorityValue { 1.f };

		bool isComplete() const noexcept;

		void
		pickBestPhysicalDeviceQueues(
			const std::vector<VkQueueFamilyProperties>& p_queueProp,
			const VkSurfaceKHR& p_surface,
			const VkPhysicalDevice& p_device
		) noexcept;

		void
		getSetIndex(std::set<uint32_t>& p_set) const noexcept;

		private:

		void
		checkGraphicQueueIndex(
			const VkQueueFamilyProperties& p_prop,
			const int& p_queueId
		) noexcept;

		void checkPresentQueueIndex(
			const VkQueueFamilyProperties& p_prop,
			const int& p_queueId,
			const VkSurfaceKHR& p_surface,
			const VkPhysicalDevice& p_device
		) noexcept;

	};
}