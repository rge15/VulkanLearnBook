#pragma once
#include <utilities/graphicsInclude.hpp>
#include <utilities/TypeAliases.hpp>
#include <engine/VKObjects/RenderPipeline/PipelineLayout.hpp>

namespace Graphics
{
	class VRenderManager
	{
	
	private:


		//Pipeline Layout
		UniqPtr<PipelineLayout> _pipelineLayout { nullptr };
		//Render Pass
		// UniqPtr<VkRenderPass> _renderPass { nullptr };
		//VkPipeline
		// UniqPtr<VkPipeline> _renderPipeline { nullptr };

	public:

		//TODO : Aquí hará falta tmbn el SwapChainInfo
		VRenderManager( VkDevice& p_device ) noexcept;
		~VRenderManager() = default;
	};

}