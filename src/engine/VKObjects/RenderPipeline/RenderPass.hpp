#pragma once
#include <utilities/graphicsInclude.hpp>
#include <utilities/TypeAliases.hpp>
#include <utilities/assertMacros.hpp> 
#include <engine/VKObjects/Managers/utils/SwapchainInfo.hpp>

namespace Graphics
{
	class RenderPass
	{
	private:
		const Manager::SwapchainInfo& _swapchainInfo;

		VkRenderPassCreateInfo _createInfo {};

		Vector<VkAttachmentDescription> _attachmentDescriptor {};
		Vector<VkSubpassDescription> _subpassDescriptor {};
		Vector<VkAttachmentReference> _attachmentReferences {};
		Vector<VkSubpassDependency> _subpassDependencies {};

		void
		initDistyInfoInANastyWay() noexcept;

		void
		initInfo() noexcept;

		void
		createRenderPass() noexcept;

	public:
		RenderPass(const Manager::SwapchainInfo& p_swapInfo) noexcept;
		~RenderPass() = default;
	};	
}