#pragma once
#include <utilities/graphicsInclude.hpp>
#include <utilities/TypeAliases.hpp>
#include <engine/VKObjects/RenderPipeline/PipelineLayout.hpp>
#include <engine/VKObjects/RenderPipeline/RenderPass.hpp>
#include <engine/VKObjects/RenderPipeline/RenderPipeline.hpp>
#include <engine/VKObjects/Resources/VShader.hpp> 
#include <engine/VKObjects/RenderPipeline/RenderDrawer.hpp>


namespace Graphics
{
	class VRenderManager
	{
	public:
		Manager::SwapchainManager& _swapManager;

	private:
		VkDevice& _ownerDevice;
		Manager::QueueManager& _queueManager;
		//--------------------------------------------------//
		//				VK Render Configuration				//
		//--------------------------------------------------//
		//Pipeline Layout
		UniqPtr<PipelineLayout> _pipelineLayout { nullptr };
		//Render Pass
		UniqPtr<RenderPass> _renderPass { nullptr };
		//VkPipeline
		UniqPtr<RenderPipeline> _renderPipeline { nullptr };

		Vector<VkPipelineShaderStageCreateInfo> _pipelineShaders {};

		Vector<VkFramebuffer> _swapchainFramebuffers {};

		//--------------------------------------------------//
		//				VK Draw Configuration				//
		//--------------------------------------------------//
		//TODO : Este RenderDrawer tendrá el Cmnd Pool y el Cmnd Buffer
		UniqPtr<RenderDrawer> _renderDrawer { nullptr };


	public:

		VRenderManager(
			VkDevice& p_device,
			Manager::SwapchainManager& p_swapchainManager,
			Manager::QueueManager& p_queueManager
		) noexcept;

		~VRenderManager();

		void
		addPipelineShaderStages( VkPipelineShaderStageCreateInfo& p_shader ) noexcept;

		void
		setUpRenderPipeline() noexcept;

		void
		prepareRenderPipelineDrawing() noexcept;

		RenderDrawer* const
		getDrawer() const noexcept;

	private:
	
		void
		createRenderPipeline() noexcept;

		void
		createFrameBuffers() noexcept;

	};

}