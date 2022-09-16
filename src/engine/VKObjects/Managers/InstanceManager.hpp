#include "../../../utilities/config.hpp"
#include "../../../utilities/TypeAliases.hpp"
#include "../../../utilities/assertMacros.hpp"
#include <vulkan/vulkan.h>

//TODO : Ahora vamos a hacer lo mismo que hemos hecho con este manager pero para el physical device
//TODO : y convertir los dos como Uniq_ptr en el VDriver.hpp


namespace Graphics::Managers
{
	class Instance{
		private:

			VkApplicationInfo _appInfo {};
			VkInstanceCreateInfo _instanceInfo {};
			VkInstance _instance { VK_NULL_HANDLE };

		public:

			Instance(
				char* p_appName = "App", char* p_engineName = "Engine",
				uint32_t appVer = 1, uint32_t engineVer = 1
			) noexcept;

			~Instance() noexcept;

		private:

			void initInstanceData() noexcept;

			void initInstance() noexcept;

	};
}