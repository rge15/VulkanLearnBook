#include <utilities/config.hpp>
#include <utilities/TypeAliases.hpp>
#include <utilities/assertMacros.hpp>
#include "../Helpers/GetVKObjects.hpp"
#include "InstanceManager.hpp"
#include <vulkan/vulkan.h>
#include "QueueManager.hpp"
#include "SwapchainManager.hpp"

namespace Graphics::Manager
{
	class Device
	{
		private:

			Instance& _engineInstance;
			GLFWwindow& _window;

			VkPhysicalDevice _phDevice { VK_NULL_HANDLE };
			VkDevice _device { VK_NULL_HANDLE };

			VkDeviceCreateInfo 			_deviceInfo 	{};
			VkPhysicalDeviceFeatures 	_deviceFeature 	{};

			const std::vector<const char*> _requiredDeviceExtensions = {
    			VK_KHR_SWAPCHAIN_EXTENSION_NAME
			};

			VkSurfaceKHR _surface {};

			QueueManager 	_queueManager			{};
			VkQueue			_presentQueueHandler	{};
			VkQueue			_graphicsQueueHandler	{};

			SwapchainManager _swapchain {};

		public:

			/** @brief Default constructor of class Device */
			explicit Device( Instance& p_vkInstance, GLFWwindow& p_window )	noexcept;

			/** @brief Default destructor of class Device */
			~Device() noexcept;
			//? Ir haciendo los getters en ir haciendo falta

			/**
			 *	@brief Gets the vulkan logical device once created
			 *
			 * 	@return Reference to the Vulkan Logical Device
			*/
			VkDevice&
			getVkDevice() noexcept { return _device; }

			/**
			 *	@brief Gets the vulkan Swapchain manager
			 *
			 * 	@return Reference to the Vulkan Swapchain manager
			*/
			const SwapchainManager&
			getSwapchainManager() const noexcept { return _swapchain; }


		private:

			/**
			 * 	@brief Gets the physical device that best fits the app requeriments
			*/
			void getPhysicalDevice() noexcept;

			/**
			 * 	@brief Checks all the requeriments for the passed physical device
			 * 
			 * 	@param p_device Physical device to check
			*/
			bool getSuitableDevice( VkPhysicalDevice& p_device ) noexcept;

			/**
			 * 	@brief Checks all the queue suitability requeriments for the passed physical device
			 * 
			 * 	@param p_device Physical device to check
			*/
			bool checkQueuesSuitability( VkPhysicalDevice& p_device ) noexcept;

			/**
			 * 	@brief Checks all the extensions suitability requeriments for the passed physical device
			 * 
			 * 	@param p_device Physical device to check
			*/
			bool checkExtensionsSuitability( VkPhysicalDevice& p_device ) noexcept;

			/**
			 * 	@brief Inits the features requeriments for the logical device
			*/
			void initFeatureRequeriments() noexcept;

			/**
			 * 	@brief Sets the queue creation info
			*/
			void initQueueCreateInfo() noexcept;

			/**
			 * 	@brief Sets the logical device creation info
			*/
			void initCreationInfo() noexcept;

			/**
			 * 	@brief Creates the Vulkan logical Device
			*/
			void createDevice() noexcept;

			/**
			 * 	@brief Updates all the related queue data
			*/
			void updateQueueData() noexcept;
			
			/**
			 * 	@brief Gets the Vulkan Surface to render in
			*/
			void getSurfaceDisplay() noexcept;

			/**
			 *	@brief Create swapchain related to the logical device
			*/
			void createSwapchain() noexcept;

	};
}