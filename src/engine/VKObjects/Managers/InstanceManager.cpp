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
		createInstance();

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

	void Instance::createInstance() noexcept
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
		_instanceInfo.ppEnabledExtensionNames = { glfwExtensions };

#ifdef DEBUG
		setLayerInfo();
#else
		_instanceInfo.enabledLayerCount = { 0 };
		_instanceInfo.ppEnabledLayerNames = { VK_NO_LAYERS };
#endif
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

#ifdef DEBUG
	void Instance::setLayerInfo() noexcept
	{
		uint32_t layerCount { 0 };
		vkEnumerateInstanceLayerProperties( &layerCount, nullptr);
		std::vector<VkLayerProperties> layers( layerCount );
		vkEnumerateInstanceLayerProperties( &layerCount, layers.data());
	
		checkAndSetLayers( layers );
	}
#endif

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

#ifdef DEBUG
	void Instance::checkAndSetLayers(const std::vector<VkLayerProperties>& p_availibleLayers ) noexcept
	{
		bool layerFound { false };
		for(auto& neededLayer : _validationLayers)
		{
			layerFound = false;
			for(auto& availibleLayer : p_availibleLayers)
			{
				if( std::strcmp( neededLayer, availibleLayer.layerName ) == 0 )
				{
					std::cout << "Layer " << neededLayer << " in use ;D" << std::endl;
					layerFound = true;
					break;
				}
			}

			if( !layerFound )
			{
				std::cout << "Layer named : " << neededLayer << " is not suported." << std::endl;
				ASSERT( layerFound, "Layer specified not supported ;c")
			}
		}

		_instanceInfo.enabledLayerCount = { (uint32_t)_validationLayers.size() };
		_instanceInfo.ppEnabledLayerNames = { _validationLayers.data() };
	}
#endif
}