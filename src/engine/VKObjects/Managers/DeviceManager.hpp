#include <utilities/config.hpp>
#include <utilities/TypeAliases.hpp>
#include <utilities/assertMacros.hpp>
#include "../Helpers/GetVKObjects.hpp"
#include "utils/QueueFamilyInfo.hpp"
#include "InstanceManager.hpp"
#include <vulkan/vulkan.h>


namespace Graphics::Manager
{
	class Device
	{
		private:

			Instance& _engineInstance;

			VkDevice _device { VK_NULL_HANDLE };

			VkPhysicalDevice _phDevice { VK_NULL_HANDLE };

			VkDeviceCreateInfo 			_deviceInfo 	{};
			VkPhysicalDeviceFeatures 	_deviceFeature 	{};
			VkDeviceQueueCreateInfo 	_queueInfo 		{};
			QueueFamilyInfo 			_queueIndexInfo	{};

			//?Entiendo que el manejador de la QUEUE tendrá que ir en una clase aparte para hacer paridas de colas
			VkQueue	_queueHandler {};

		public:

			Device( Instance& p_vkInstance )	noexcept;

			~Device() noexcept;

		private:

			void getPhysicalDevice() noexcept;

			void initFeatureRequeriments() noexcept;

			void initQueueCreateInfo() noexcept;

			void initCreationInfo() noexcept;

			void createDevice() noexcept;

			void getQueueHandler() noexcept;
	};
}