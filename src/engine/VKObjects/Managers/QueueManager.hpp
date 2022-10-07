#pragma once
#include <utilities/config.hpp>
#include <vulkan/vulkan.h>
#include "utils/QueueFamilyInfo.hpp"
#include "../Helpers/GetVKObjects.hpp"

namespace Graphics::Manager
{
	class QueueManager
	{
		private:
			std::vector<VkDeviceQueueCreateInfo> _queueInfo	{};
			QueueFamilyInfo _queueIndexInfo	{};

		public:
			QueueManager() noexcept = default;

			~QueueManager() noexcept = default;

			bool 
			checkQueuesSuitability( VkPhysicalDevice& p_device, VkSurfaceKHR& p_surface ) noexcept;

			void 
			initQueueCreateInfo() noexcept;

			int32_t
			queueCount() noexcept { return _queueInfo.size(); }

			VkDeviceQueueCreateInfo*
			queueData() noexcept { return _queueInfo.data(); }

			void
			getGraphicHandler( VkDevice& p_device, VkQueue& p_queueHandler) const noexcept;

			void
			getPresentHandler( VkDevice& p_device, VkQueue& p_queueHandler) const noexcept;

	};
}