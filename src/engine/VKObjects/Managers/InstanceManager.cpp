#include "InstanceManager.hpp"

namespace Graphics::Manager
{

	Instance::Instance(
		string p_appName, string p_engineName,
		uint32_t appVer, uint32_t engineVer) noexcept
	{
		_appInfo.sType = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
		_appInfo.pNext = { nullptr };
		_appInfo.pEngineName = { p_engineName.data() };
		_appInfo.pApplicationName = { p_appName.data() };
		_appInfo.applicationVersion = { appVer };
		_appInfo.engineVersion = { engineVer };
		_appInfo.apiVersion = { VK_MAKE_VERSION(1,0,0) };

		initInstanceData();
		initInstance();

	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	Instance::~Instance() noexcept
	{
		vkDestroyInstance(
			_instance,
			nullptr
		);
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

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

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void Instance::initInstanceData() noexcept
	{
		uint32_t glfwCountExtension {0};
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwCountExtension);

		_instanceInfo.sType = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
		_instanceInfo.pNext = { nullptr };
		_instanceInfo.pApplicationInfo = { &_appInfo };
		_instanceInfo.flags = { 0 };
		_instanceInfo.enabledExtensionCount = { glfwCountExtension };
		_instanceInfo.enabledLayerCount = { 0 };
		_instanceInfo.ppEnabledExtensionNames = { glfwExtensions };
		_instanceInfo.ppEnabledLayerNames = { VK_NO_LAYERS };
	}

}