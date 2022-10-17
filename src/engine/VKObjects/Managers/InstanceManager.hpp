#pragma once
#include <utilities/config.hpp>
#include <utilities/TypeAliases.hpp>
#include <utilities/assertMacros.hpp>
#include <utilities/graphicsInclude.hpp>

namespace Graphics::Manager
{
	class Instance{
		private:

			VkApplicationInfo _appInfo {};
			VkInstanceCreateInfo _instanceInfo {};
			VkInstance _instance { VK_NULL_HANDLE };

#ifdef DEBUG
			const std::vector<const char*> _validationLayers = 
			{
				"VK_LAYER_KHRONOS_validation"
			};
#endif

		public:

			/** @brief Constructor of Instance Class
			 * 
			 * 	@param p_appName Name of the app
			 * 	@param p_engineName Name of the engine
			 * 	@param p_appVer Version of the app
			 * 	@param p_appVer Version of the engine
			 * 
			 */
			Instance(
				string p_appName = "App", string p_engineName = "Engine",
				uint32_t appVer = 1, uint32_t engineVer = 1
			) noexcept;

			/** @brief Instance class destructor */
			~Instance() noexcept;

			/**
			 * 	@brief Gets the reference to the Vulkan Instance
			 * 
			 * 	@return Reference to the Vulkan Instance
			*/
			VkInstance& getInstance()
			{
				return _instance;
			}

			/**
			 * 	@brief Gets the reference to the Vulkan Creation Instance Information
			 * 
			 * 	@return Reference to the Vulkan Creation Instance Information
			*/
			VkInstanceCreateInfo& getInstanceInfo()
			{
				return _instanceInfo;
			}

		private:

			/**
			 * 	@brief Starts the data for the instance creation
			*/
			void initInstanceData() noexcept;

			/**
			 * 	@brief Creates the Vulkan Instsance
			*/
			void createInstance() noexcept;

#ifdef DEBUG
			/**
			 * 	@brief Sets the Vulkan Layer information
			*/
			void setLayerInfo() noexcept;
#endif

#ifdef DEBUG
			/**
			 * 	@brief Checks if the instance can manage the required layer extension
			*/
			void checkAndSetLayers(const std::vector<VkLayerProperties>& p_availibleLayers ) noexcept;
#endif
	};
}