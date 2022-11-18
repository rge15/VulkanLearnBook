#pragma once
#include <utilities/graphicsInclude.hpp>
#include <utilities/TypeAliases.hpp>
#include <engine/VKObjects/Managers/utils/SwapchainInfo.hpp>

namespace Graphics
{
	struct GraphicPipelineConfigutarion
	{
		const Manager::SwapchainInfo& _swapchainInfo;

		Vector<VkDynamicState> _dynamicStates {};
		VkPipelineDynamicStateCreateInfo _dynamicInfo {};
		
		VkViewport _viewport	{};
		VkRect2D _scissor 		{};
		VkPipelineViewportStateCreateInfo _viewportInfo {};

		VkPipelineColorBlendAttachmentState _colorBlendAttach {};
		VkPipelineColorBlendStateCreateInfo _colorBlendInfo {};
		VkPipelineDepthStencilStateCreateInfo _stencilAndDepthInfo {};

		VkPipelineVertexInputStateCreateInfo _vertexInfo {};
		VkPipelineInputAssemblyStateCreateInfo _assemblyCreateInfo {};

		VkPipelineRasterizationStateCreateInfo _rasterInfo {};
		VkPipelineMultisampleStateCreateInfo _multiplesampleCreateInfo {};

		GraphicPipelineConfigutarion(const Manager::SwapchainInfo& p_swap) noexcept;

		private:
			void
			initConfig() noexcept;

			void
			colorConfig() noexcept;

			void
			depthStencilConfig() noexcept;

			void
			rasterConfig() noexcept;

			void
			multisampleConfig() noexcept;

			void
			assemblyConfig() noexcept;

			void
			vertexConfig() noexcept;

			void
			dynamicStateConfig() noexcept;

			void
			viewportStateConfig() noexcept;
	};
}
