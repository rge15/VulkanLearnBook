#include "RenderPipeline.hpp"

namespace Graphics
{
	RenderPipeline::RenderPipeline(
		VkDevice& p_device,
		VkPipelineLayout& p_layout,
		VkRenderPass& p_renderPass,
		const Manager::SwapchainInfo& p_swapchainInfo
	) noexcept
	: _ownerDevice{p_device}, _pipelineLayout { p_layout }, _renderPass { p_renderPass }, _pipelineConfig{ p_swapchainInfo }
	{
		initCreateInfo();
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	RenderPipeline::~RenderPipeline()
	{
		if(_pipeline != VK_NULL_HANDLE)
			vkDestroyPipeline( _ownerDevice, _pipeline, nullptr );
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	RenderPipeline::initCreateInfo() noexcept
	{
		_createInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		_createInfo.pNext = nullptr;
		_createInfo.subpass = 0;
		_createInfo.renderPass = _renderPass;
		_createInfo.layout = _pipelineLayout;
	
		_createInfo.basePipelineIndex = -1;
		_createInfo.basePipelineHandle = VK_NULL_HANDLE;

		_createInfo.pColorBlendState = &_pipelineConfig._colorBlendInfo;
		_createInfo.pDynamicState = &_pipelineConfig._dynamicInfo;
		_createInfo.pInputAssemblyState = &_pipelineConfig._assemblyCreateInfo;
		_createInfo.pMultisampleState = &_pipelineConfig._multiplesampleCreateInfo;
		_createInfo.pRasterizationState = &_pipelineConfig._rasterInfo;
		_createInfo.pVertexInputState = &_pipelineConfig._vertexInfo;
		_createInfo.pViewportState = &_pipelineConfig._viewportInfo;
		_createInfo.pDepthStencilState = nullptr;
		_createInfo.pTessellationState = nullptr;
	
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	RenderPipeline::createPipeline() noexcept
	{
		auto vkResult = vkCreateGraphicsPipelines( _ownerDevice, VK_NULL_HANDLE, 1, &_createInfo, nullptr, &_pipeline );
	
		ASSERT((vkResult == VK_SUCCESS), "RenderPipeline creation failed ;c")

		std::cout << "RenderPipeline creation SUCCED :D\n";
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	RenderPipeline::setShaderStages( Vector<VkPipelineShaderStageCreateInfo>& p_shaders ) noexcept
	{
		_createInfo.stageCount = (uint32_t)p_shaders.size();
		_createInfo.pStages = p_shaders.data(); 
	}

}