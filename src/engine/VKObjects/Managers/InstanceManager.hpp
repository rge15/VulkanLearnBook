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

			Instance(
				string p_appName = "App", string p_engineName = "Engine",
				uint32_t appVer = 1, uint32_t engineVer = 1
			) noexcept;

			~Instance() noexcept;

			VkInstance& getInstance()
			{
				return _instance;
			}

			VkInstanceCreateInfo& getInstanceInfo()
			{
				return _instanceInfo;
			}

		private:

			void initInstanceData() noexcept;

			void initInstance() noexcept;

#ifdef DEBUG
			void setLayerInfo() noexcept;
#endif

#ifdef DEBUG
			void checkAndSetLayers(const std::vector<VkLayerProperties>& p_availibleLayers ) noexcept;
#endif
	};
}