#pragma once
#include <utilities/graphicsInclude.hpp>
#include <engine/VKObjects/RenderPipeline/GraphicConfigutarion.hpp>

namespace Graphics
{
	class RenderPipeline
	{
	private:
		VkDevice& _ownerDevice;
		VkPipelineLayout& _pipelineLayout;
		VkRenderPass& _renderPass;

		GraphicPipelineConfigutarion _pipelineConfig;

		VkGraphicsPipelineCreateInfo _createInfo {};

		void
		initCreateInfo() noexcept;

	public:
		VkPipeline _pipeline { VK_NULL_HANDLE };

		RenderPipeline(
			VkDevice& p_device,
			VkPipelineLayout& p_layout,
			VkRenderPass& p_renderPass,
			const Manager::SwapchainInfo& p_swapchainInfo ) noexcept;

		~RenderPipeline() noexcept;

		void
		createPipeline() noexcept;

		void
		setShaderStages( Vector<VkPipelineShaderStageCreateInfo>& p_shaders ) noexcept;

	};	
}