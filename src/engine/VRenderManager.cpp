#include "VRenderManager.hpp"

namespace Graphics
{

	VRenderManager::VRenderManager( 
		VkDevice& p_device, const Manager::SwapchainInfo& p_swapchainInfo
	) noexcept
	: _pipelineLayout { std::make_unique<PipelineLayout>( p_device ) }
	, _renderPass { std::make_unique<RenderPass>( p_swapchainInfo ) }
	{
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

}