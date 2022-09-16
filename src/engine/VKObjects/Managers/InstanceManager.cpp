#include "InstanceManager.hpp"

namespace Graphics::Managers
{

	Instance::Instance(
		char* p_appName = "App", char* p_engineName = "Engine",
		uint32_t appVer = 1, uint32_t engineVer = 1 ) noexcept
	{
		_appInfo.sType = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
		_appInfo.pNext = { nullptr };
		_appInfo.pEngineName = { p_engineName };
		_appInfo.pApplicationName = { p_appName };
		_appInfo.applicationVersion = { appVer };
		_appInfo.engineVersion = { engineVer };
		_appInfo.apiVersion = { VK_MAKE_VERSION(1,0,0) };

		initInstanceData();
		initInstance();

	}

	Instance::~Instance() noexcept
	{

	}

	void Instance::initInstance() noexcept
	{
		VkResult result = vkCreateInstance(
			&_instanceInfo,
			nullptr,
			&_instance
		);

		ASSERT( result == VK_SUCCESS, "Errors creating VK Instance ;c")

		if(	result == VK_SUCCESS )
			std::cout << "Bien creada la instancia crack, a ver los device" << std::endl;
	}

	void Instance::initInstanceData() noexcept
	{
		_instanceInfo.sType = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
		_instanceInfo.pNext = { nullptr };
		_instanceInfo.pApplicationInfo = { &_appInfo };
		_instanceInfo.flags = { 0 };
		_instanceInfo.enabledExtensionCount = { 0 };
		_instanceInfo.enabledLayerCount = { 0 };
		_instanceInfo.ppEnabledExtensionNames = { VK_NO_EXTENSIONS };
		_instanceInfo.ppEnabledLayerNames = { VK_NO_LAYERS };
	}
}