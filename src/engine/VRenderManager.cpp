#include "VRenderManager.hpp"

namespace Graphics
{

	VRenderManager::VRenderManager( VkDevice& p_device) noexcept
	: _pipelineLayout { std::make_unique<PipelineLayout>( p_device ) }
	{
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}