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

		private:

			void initInstanceData() noexcept;

			void initInstance() noexcept;

	};
}