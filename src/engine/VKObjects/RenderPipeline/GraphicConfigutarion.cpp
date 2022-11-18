#include "GraphicConfigutarion.hpp"

namespace Graphics
{
	GraphicPipelineConfigutarion::GraphicPipelineConfigutarion(const Manager::SwapchainInfo& p_swap) noexcept
	: _swapchainInfo { p_swap }
	{
		initConfig();
	}

	void
	GraphicPipelineConfigutarion::initConfig() noexcept
	{
		colorConfig();
		depthStencilConfig();

		viewportStateConfig();
		dynamicStateConfig();

		assemblyConfig();
		vertexConfig();

		rasterConfig();
		multisampleConfig();
	}

	void
	GraphicPipelineConfigutarion::colorConfig() noexcept
	{
		_colorBlendAttach.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		_colorBlendAttach.blendEnable = VK_FALSE;

		//If blendEnable == VK_FALSE this doesn't affect
		//{ 		
		_colorBlendAttach.colorBlendOp = VK_BLEND_OP_ADD;
		_colorBlendAttach.alphaBlendOp = VK_BLEND_OP_ADD;

		_colorBlendAttach.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
		_colorBlendAttach.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;

		_colorBlendAttach.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
		_colorBlendAttach.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		//}
		
		_colorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		_colorBlendInfo.pNext = nullptr;

		_colorBlendInfo.logicOpEnable = VK_FALSE;

		//If logicOpEnable == VK_TRUE this affect
		//{
			_colorBlendInfo.logicOp = VK_LOGIC_OP_COPY;
			_colorBlendInfo.blendConstants[0] = 0.0f;
			_colorBlendInfo.blendConstants[1] = 0.0f;
			_colorBlendInfo.blendConstants[2] = 0.0f;
			_colorBlendInfo.blendConstants[3] = 0.0f;
		//} else {
			_colorBlendInfo.attachmentCount = 1;
			_colorBlendInfo.pAttachments = &_colorBlendAttach;
		//}
	}

	void
	GraphicPipelineConfigutarion::depthStencilConfig() noexcept
	{
		//Right Now dissabled
	}

	void
	GraphicPipelineConfigutarion::rasterConfig() noexcept
	{
		_rasterInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		_rasterInfo.pNext = nullptr;
		_rasterInfo.polygonMode = VK_POLYGON_MODE_FILL;
		_rasterInfo.lineWidth = 1.0f;
		_rasterInfo.rasterizerDiscardEnable = VK_FALSE;

		_rasterInfo.cullMode = VK_CULL_MODE_BACK_BIT;
		_rasterInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;

		_rasterInfo.depthClampEnable = VK_FALSE;
		_rasterInfo.depthBiasEnable = VK_FALSE;
		_rasterInfo.depthBiasClamp = 0.0f;
		_rasterInfo.depthBiasConstantFactor = 0.0f;
		_rasterInfo.depthBiasSlopeFactor = 0.0f;
	}

	void
	GraphicPipelineConfigutarion::multisampleConfig() noexcept
	{
		_multiplesampleCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		_multiplesampleCreateInfo.pNext = nullptr;
		_multiplesampleCreateInfo.sampleShadingEnable = VK_FALSE;
		_multiplesampleCreateInfo.rasterizationSamples= VK_SAMPLE_COUNT_1_BIT;
		_multiplesampleCreateInfo.minSampleShading = 1.0f;
		_multiplesampleCreateInfo.pSampleMask = nullptr;
		_multiplesampleCreateInfo.alphaToOneEnable = VK_FALSE;
		_multiplesampleCreateInfo.alphaToCoverageEnable = VK_FALSE;
	}

	void
	GraphicPipelineConfigutarion::assemblyConfig() noexcept
	{
		_assemblyCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		_assemblyCreateInfo.pNext = nullptr;
		_assemblyCreateInfo.primitiveRestartEnable = VK_FALSE;
		_assemblyCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	}

	void
	GraphicPipelineConfigutarion::vertexConfig() noexcept
	{
		_vertexInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		_vertexInfo.pNext = nullptr;
		_vertexInfo.vertexAttributeDescriptionCount = 0;
		_vertexInfo.pVertexAttributeDescriptions = nullptr;
		_vertexInfo.vertexBindingDescriptionCount = 0;
		_vertexInfo.pVertexBindingDescriptions = nullptr;
	}

	void
	GraphicPipelineConfigutarion::dynamicStateConfig() noexcept
	{
		_dynamicStates.push_back( VK_DYNAMIC_STATE_VIEWPORT );
		_dynamicStates.push_back( VK_DYNAMIC_STATE_SCISSOR );
	
		_dynamicInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		_dynamicInfo.pNext = nullptr;
		_dynamicInfo.dynamicStateCount = (uint32_t)_dynamicStates.size();
		_dynamicInfo.pDynamicStates = _dynamicStates.data();
	}

	void
	GraphicPipelineConfigutarion::viewportStateConfig() noexcept
	{
		_viewport.x = 0;
		_viewport.y = 0;
		_viewport.height = _swapchainInfo._swapchainExtent.height;
		_viewport.width = _swapchainInfo._swapchainExtent.width;
		_viewport.minDepth = 0.0f;
		_viewport.maxDepth = 1.0f;

		_scissor.offset = { 0 , 0 };
		_scissor.extent = _swapchainInfo._swapchainExtent;

		_viewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		_viewportInfo.pNext = nullptr;
		_viewportInfo.viewportCount = 1;
		_viewportInfo.pViewports = &_viewport;
		_viewportInfo.scissorCount = 1;
		_viewportInfo.pScissors = &_scissor;
	}


}