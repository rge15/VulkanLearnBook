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
		VkDevice& _ownerDevice;

		VkRenderPassCreateInfo _createInfo {};

		Vector<VkAttachmentDescription> _attachmentDescriptor {};
		Vector<VkAttachmentReference> _attachmentReferences {};
		Vector<VkSubpassDescription> _subpassDescriptor {};

		void
		initDistyInfoInANastyWay() noexcept;

		void
		initInfo() noexcept;

		void
		createRenderPass() noexcept;
	public:
		const Manager::SwapchainInfo& _swapchainInfo;

		VkRenderPass _renderPass;

	public:
		RenderPass( VkDevice& p_device ,const Manager::SwapchainInfo& p_swapInfo) noexcept;
		~RenderPass() noexcept;
	};
}