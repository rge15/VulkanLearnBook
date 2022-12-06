#include "RenderDrawer.hpp"

namespace Graphics
{
    RenderDrawer::RenderDrawer(
        VkDevice& p_device, 
        const Manager::SwapchainManager& p_swapchainManager,
        const Manager::QueueManager& p_queueManager,
		RenderPipeline& p_renderPipeline,
        Vector<VkFramebuffer>& p_frameBuffers
	) noexcept
    : _ownerDevice { p_device }
    , _swapManager { p_swapchainManager }
    , _queueManager { p_queueManager }
    , _renderPipeline { p_renderPipeline }
	, _frameBuffers { p_frameBuffers }
	{
        reserveCommandPool();
        allocateCommandBuffer();
    }

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

    RenderDrawer::~RenderDrawer() noexcept
	{
		vkDestroyCommandPool( _ownerDevice, _cmdPool, nullptr );
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	RenderDrawer::reserveCommandPool() noexcept
	{
		VkCommandPoolCreateInfo poolCreateInfo {};

		poolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolCreateInfo.pNext = nullptr;
		poolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		poolCreateInfo.queueFamilyIndex = _queueManager.getGraphicQueueId();

		VkResult result = vkCreateCommandPool( _ownerDevice, &poolCreateInfo, nullptr, &_cmdPool );

		ASSERT( (result==VK_SUCCESS), "Error reserving the Command Pool (:vC) " )

		std::cout << " Command Pool created very well (:vD) " << '\n';
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	RenderDrawer::allocateCommandBuffer() noexcept
	{
		VkCommandBufferAllocateInfo allocateInfo {};
		
		allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocateInfo.pNext = nullptr;
		allocateInfo.commandPool = _cmdPool;
		allocateInfo.commandBufferCount = 1;
		allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

		VkResult result = vkAllocateCommandBuffers( _ownerDevice, &allocateInfo, &_cmdBuffer );

		ASSERT( (result==VK_SUCCESS), "Error allocating the Command Buffer (:vC) " )

		std::cout << " Command Buffer created very well (:vD) " << '\n';	
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	//TODO : Hacer el record de el commando de dibujado
	void
	RenderDrawer::recordDrawCommand( const int32_t p_imageIndex ) noexcept
	{
		beginCmdBuffer();
		renderPass( p_imageIndex );
		endCmdBuffer();
	}


	void
	RenderDrawer::beginCmdBuffer() noexcept
	{
		VkCommandBufferBeginInfo cmdBegin {};

		cmdBegin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		cmdBegin.pNext = nullptr;
		cmdBegin.flags = 0;
		cmdBegin.pInheritanceInfo = nullptr;
	
		VkResult result = vkBeginCommandBuffer( _cmdBuffer, &cmdBegin );

		ASSERT( (result==VK_SUCCESS), "Error begining the Command Buffer (:vC) " )
	}

	void
	RenderDrawer::renderPass( const int32_t p_imageIndex ) noexcept
	{
		VkRenderPassBeginInfo renderInfo {};
		VkClearValue clearColor = {0.f,0.f,0.f,1.f};

		renderInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderInfo.pNext = nullptr;
		renderInfo.renderPass = _renderPipeline._renderPass;
		renderInfo.framebuffer = _frameBuffers[p_imageIndex];
		renderInfo.renderArea.offset = { 0 , 0 };
		renderInfo.renderArea.extent = _swapManager.getSwapchainInfo()._swapchainExtent;
		renderInfo.clearValueCount = 1;
		renderInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass( _cmdBuffer, &renderInfo, VK_SUBPASS_CONTENTS_INLINE );

		vkCmdBindPipeline( _cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _renderPipeline._pipeline );

		VkViewport viewport{};

		viewport.x = 0;
		viewport.y = 0;
		viewport.height = (float)_swapManager.getSwapchainInfo()._swapchainExtent.height;
		viewport.width = (float)_swapManager.getSwapchainInfo()._swapchainExtent.width;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		vkCmdSetViewport( _cmdBuffer, 0, 1, &viewport );

		VkRect2D _scissor {};

		_scissor.offset = { 0 , 0 };
		_scissor.extent = _swapManager.getSwapchainInfo()._swapchainExtent;

		vkCmdSetScissor( _cmdBuffer, 0, 1, &_scissor );

		vkCmdDraw( _cmdBuffer, 3, 1, 0, 0);

		vkCmdEndRenderPass( _cmdBuffer );

	}

	void
	RenderDrawer::endCmdBuffer() noexcept
	{
		VkResult result = vkEndCommandBuffer(_cmdBuffer);

		ASSERT( (result==VK_SUCCESS), "Error ending the Command Buffer (:vC) " )
	}

}