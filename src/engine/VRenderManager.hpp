#pragma once
#include <utilities/graphicsInclude.hpp>
#include <utilities/TypeAliases.hpp>
#include <engine/VKObjects/RenderPipeline/PipelineLayout.hpp>
#include <engine/VKObjects/RenderPipeline/RenderPass.hpp>
#include <engine/VKObjects/RenderPipeline/RenderPipeline.hpp>
#include <engine/VKObjects/Managers/utils/SwapchainInfo.hpp>
#include <engine/VKObjects/Resources/VShader.hpp> 

namespace Graphics
{
	class VRenderManager
	{
	private:

		//Pipeline Layout
		UniqPtr<PipelineLayout> _pipelineLayout { nullptr };
		//Render Pass
		UniqPtr<RenderPass> _renderPass { nullptr };
		//VkPipeline
		UniqPtr<RenderPipeline> _renderPipeline { nullptr };

		Vector<VkPipelineShaderStageCreateInfo> _pipelineShaders {};

	public:

		VRenderManager( VkDevice& p_device, const Manager::SwapchainInfo& p_swapchainInfo ) noexcept;

		~VRenderManager() = default;

		void
		addPipelineShaderStages( VkPipelineShaderStageCreateInfo& p_shader ) noexcept;

		void
		createRenderPipeline() noexcept;
	};

}