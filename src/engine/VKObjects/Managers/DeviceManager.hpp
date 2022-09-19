#include "../../../utilities/config.hpp"
#include "../../../utilities/TypeAliases.hpp"
#include "../../../utilities/assertMacros.hpp"
#include "../Helpers/GetVKObjects.hpp"
#include <vulkan/vulkan.h>


namespace Graphics::Manager
{
	class Device
	{
		private:

			VkInstance& _engineInstance;

			VkDevice _device { VK_NULL_HANDLE };

			VkPhysicalDevice _phDevice { VK_NULL_HANDLE };

			VkDeviceCreateInfo _deviceInfo {};
			VkPhysicalDeviceFeatures _deviceFeature {};
			VkDeviceQueueCreateInfo _queueInfo {};

		public:

			Device( VkInstance& p_vkInstance )	noexcept;

			~Device() noexcept;

		private:

			void getPhysicalDevice() noexcept;

			void initFeatureRequeriments() noexcept;

			void initQueueCreateInfo() noexcept;

			void initCreationInfo() noexcept;

			void createDevice() noexcept;
	};
}