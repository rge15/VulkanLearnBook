#include "RenderPass.hpp"

namespace Graphics
{

	RenderPass::RenderPass(VkDevice& p_device ,const Manager::SwapchainInfo& p_swapInfo) noexcept
	: _ownerDevice { p_device }, _swapchainInfo { p_swapInfo }
	{
		initDistyInfoInANastyWay();
		initInfo();
		createRenderPass();
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	RenderPass::initDistyInfoInANastyWay() noexcept
	{
		VkAttachmentDescription descAttach{};
		descAttach.flags = 0;
		descAttach.format = _swapchainInfo._finalFormat.format;
		descAttach.samples = VK_SAMPLE_COUNT_1_BIT;
		descAttach.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		descAttach.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		descAttach.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		descAttach.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		descAttach.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		descAttach.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		_attachmentDescriptor.push_back( descAttach );

		VkAttachmentReference referAttach{};
		referAttach.attachment = 0;
		referAttach.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		_attachmentReferences.push_back( referAttach );

		VkSubpassDescription descSubpass{};
		descSubpass.flags = 0;
		descSubpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		descSubpass.colorAttachmentCount = 1;
		descSubpass.pColorAttachments = &_attachmentReferences.data()[0];
		

		_subpassDescriptor.push_back(descSubpass);

	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	RenderPass::initInfo() noexcept
	{
		_createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		_createInfo.pNext = nullptr;
		_createInfo.flags = 0;
		
		_createInfo.attachmentCount = _attachmentDescriptor.size();
		_createInfo.pAttachments = _attachmentDescriptor.data();
		
		_createInfo.subpassCount = _subpassDescriptor.size();
		_createInfo.pSubpasses = _subpassDescriptor.data();

		_createInfo.dependencyCount = 0;
		_createInfo.pDependencies = nullptr;
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	RenderPass::createRenderPass() noexcept
	{
		auto vkResult = vkCreateRenderPass(_ownerDevice, &_createInfo, nullptr, &_renderPass);
	
		ASSERT((vkResult == VK_SUCCESS), "RenderPass creation failed ;c")

		std::cout << "RenderPass creation SUCCED :D\n";
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	RenderPass::~RenderPass() noexcept
	{
		vkDestroyRenderPass(_ownerDevice, _renderPass, nullptr);
	}

}