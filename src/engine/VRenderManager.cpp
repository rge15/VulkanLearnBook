#include "VRenderManager.hpp"

namespace Graphics
{

	VRenderManager::VRenderManager( 
		VkDevice& p_device, const Manager::SwapchainInfo& p_swapchainInfo
	) noexcept
	: _pipelineLayout { std::make_unique<PipelineLayout>( p_device ) }
	, _renderPass { std::make_unique<RenderPass>( p_device, p_swapchainInfo ) }
	, _renderPipeline { 
		std::make_unique<RenderPipeline>( p_device,
										  _pipelineLayout.get()->_layout, 
										  _renderPass.get()->_renderPass,
										  p_swapchainInfo ) }
	{
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	VRenderManager::addPipelineShaderStages( VkPipelineShaderStageCreateInfo& p_shader ) noexcept
	{
		_pipelineShaders.push_back( p_shader );	
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	VRenderManager::createRenderPipeline() noexcept
	{
		_renderPipeline.get()->setShaderStages( _pipelineShaders );
		_renderPipeline.get()->createPipeline();
	}

}