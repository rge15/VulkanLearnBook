#pragma once
#include <utilities/graphicsInclude.hpp>
#include <utilities/TypeAliases.hpp>
#include <engine/VKObjects/RenderPipeline/PipelineLayout.hpp>
#include <engine/VKObjects/RenderPipeline/RenderPass.hpp>
#include <engine/VKObjects/RenderPipeline/RenderPipeline.hpp>
#include <engine/VKObjects/Managers/SwapchainManager.hpp>
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

		Vector<VkFramebuffer> _swapchainFramebuffers {};

		VkDevice& _ownerDevice;
		const Manager::SwapchainManager& _swapManager;

	public:

		VRenderManager( VkDevice& p_device, const Manager::SwapchainManager& p_swapchainInfo ) noexcept;

		~VRenderManager();

		void
		addPipelineShaderStages( VkPipelineShaderStageCreateInfo& p_shader ) noexcept;

		void
		setUpRenderPipeline() noexcept;

	private:
	
		void
		createRenderPipeline() noexcept;

		void
		createFrameBuffers() noexcept;

	};

}