#include "VEngine.hpp"

namespace Graphics
{

	VEngine::VEngine( const uint32_t p_w, const uint32_t p_h ) noexcept :
	_VDriver { std::make_unique<VDriver>(p_w,p_h) },
	_VResourceMngr { std::make_unique<VResourceManager>( _VDriver.get()->getVkDevice() ) },
	_VRenderMngr { std::make_unique<VRenderManager>( _VDriver.get()->getVkDevice(),
													 _VDriver.get()->getDeviceManager().getSwapchainManager(),
													 _VDriver.get()->getDeviceManager().getQueueManager() ) }
	{
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	VEngine::~VEngine() noexcept
	{
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	GLFWwindow&
	VEngine::getWindow() const noexcept
	{
		assert(_VDriver.get());
		return *_VDriver.get()->getWindow();
	}

}