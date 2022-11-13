#pragma once
#include <utilities/graphicsInclude.hpp>
#include <utilities/TypeAliases.hpp>
#include <engine/VKObjects/RenderPipeline/PipelineLayout.hpp>
#include <engine/VKObjects/RenderPipeline/RenderPass.hpp>
#include <engine/VKObjects/Managers/utils/SwapchainInfo.hpp>

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
		// UniqPtr<VkPipeline> _renderPipeline { nullptr };

	public:

		VRenderManager( VkDevice& p_device, const Manager::SwapchainInfo& p_swapchainInfo) noexcept;

		~VRenderManager() = default;
	};

}