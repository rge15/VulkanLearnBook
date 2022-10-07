#include <utilities/config.hpp>
#include <utilities/TypeAliases.hpp>
#include <utilities/assertMacros.hpp>
#include "../Helpers/GetVKObjects.hpp"
#include "utils/QueueFamilyInfo.hpp"
#include "utils/SwapchainSupportInfo.hpp"
#include "InstanceManager.hpp"
#include <vulkan/vulkan.h>


namespace Graphics::Manager
{
	class Device
	{
		private:

			Instance& _engineInstance;
			GLFWwindow& _window;

			VkDevice _device { VK_NULL_HANDLE };

			VkPhysicalDevice _phDevice { VK_NULL_HANDLE };

			VkDeviceCreateInfo 						_deviceInfo 	{};
			VkPhysicalDeviceFeatures 				_deviceFeature 	{};

			const std::vector<const char*> _requiredDeviceExt = {
    			VK_KHR_SWAPCHAIN_EXTENSION_NAME
			};

			//?Entiendo que el manejador de la SURFACE tendrá que ir en una clase aparte para hacer paridas de colas
			VkSurfaceKHR _surface {};

			//?Entiendo que el manejador de la QUEUE tendrá que ir en una clase aparte para hacer paridas de colas
			//TODO : Hacer una clase queueManager que maneje los tipos de cola que necesites y el manejo de las vkqueue
			//TODO : y que maneje tmbn el tema de la destrucción de las colas para que no haya double free ni pitos
			//TODO : 1º Hacer un unordered map, autoindexado id++, cuando no encuentre el vkQueue cree uno y lo pasé
			//todo : 	si lo encuentra que lo devuelta y que los vkqueue se conviertan en un enum class de tipos de 
			//todo :	colas que se dirijan a la unorderedmap para encontrar el vkqueue handler
			std::vector<VkDeviceQueueCreateInfo>	_queueInfo 		{};
			QueueFamilyInfo _queueIndexInfo	{};
			// VkQueue			_presentQueueHandler {};
			VkQueue			_graphicsQueueHandler {};

			//TODO : Hacer clase swapchain handler que maneje toda la parida de swapchain y quitar el máximo número de cosas de aquí
			// VkSwapchainKHR _swapchain {};


		public:

			Device( Instance& p_vkInstance, GLFWwindow& p_window )	noexcept;

			~Device() noexcept;

		private:

			void getPhysicalDevice() noexcept;

			bool getSuitableDevice( VkPhysicalDevice& p_device ) noexcept;

			bool checkQueuesSuitability( VkPhysicalDevice& p_device ) noexcept;

			bool checkExtensionsSuitability( VkPhysicalDevice& p_device ) noexcept;

			bool checkSwapchainSuitability( VkPhysicalDevice& p_device ) noexcept;

			void initFeatureRequeriments() noexcept;

			void initQueueCreateInfo() noexcept;

			void initCreationInfo() noexcept;

			void createDevice() noexcept;

			void getQueueHandler() noexcept;
			
			void getSurfaceDisplay() noexcept;
	};
}