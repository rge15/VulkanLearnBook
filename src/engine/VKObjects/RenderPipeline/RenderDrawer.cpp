#include "RenderDrawer.hpp"

namespace Graphics
{
    RenderDrawer::RenderDrawer(
        VkDevice& p_device, 
        Manager::SwapchainManager& p_swapchainManager,
        Manager::QueueManager& p_queueManager,
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
		createSyncObjects();
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

	void
	RenderDrawer::recordDrawCommand( const int32_t p_imageIndex ) noexcept
	{
		beginRecordCmdBuffer();
		renderPass( p_imageIndex );
		endRecordCmdBuffer();
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	RenderDrawer::beginRecordCmdBuffer() noexcept
	{
		VkCommandBufferBeginInfo cmdBegin {};

		cmdBegin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		cmdBegin.pNext = nullptr;
		cmdBegin.flags = 0;
		cmdBegin.pInheritanceInfo = nullptr;
	
		VkResult result = vkBeginCommandBuffer( _cmdBuffer, &cmdBegin );

		ASSERT( (result==VK_SUCCESS), "Error begining the Command Buffer (:vC) " )

	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	RenderDrawer::endRecordCmdBuffer() noexcept
	{
		VkResult result = vkEndCommandBuffer(_cmdBuffer);

		ASSERT( (result==VK_SUCCESS), "Error ending the Command Buffer (:vC) " )
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	RenderDrawer::draw() noexcept
	{
		vkWaitForFences( _ownerDevice, 1, &_frameRenderedFence, VK_TRUE, UINT64_MAX );
		vkResetFences( _ownerDevice, 1, &_frameRenderedFence );
		
		uint32_t imageIndex {};

		//TODO : Aquí el owner device debe ser el de la swapchain, no el de renderDrawer
		//Get SwapchainImage
		vkAcquireNextImageKHR( _ownerDevice, _swapManager._swapchain, UINT64_MAX, _imageReadySemaphore, VK_NULL_HANDLE, &imageIndex);

		//Record Cmd
		vkResetCommandBuffer( _cmdBuffer, 0 );
		recordDrawCommand( imageIndex );

		//Submit Cmd
		VkSubmitInfo _submitInfo {};
		const VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

		_submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		_submitInfo.pNext = nullptr;
		_submitInfo.commandBufferCount = 1;
		_submitInfo.pCommandBuffers = &_cmdBuffer;
		_submitInfo.waitSemaphoreCount = 1;
		_submitInfo.pWaitSemaphores = &_imageReadySemaphore;
		_submitInfo.signalSemaphoreCount = 1;
		_submitInfo.pSignalSemaphores = &_renderFinishedSemaphore;
		_submitInfo.pWaitDstStageMask = &waitStage;

		//TODO : Obtener el graphicQueueHandler
		VkResult result = vkQueueSubmit( _queueManager.getGraphicQueueHandler() , 1, &_submitInfo, _frameRenderedFence );
		ASSERT( (result==VK_SUCCESS), "Error submiting command buffer (:vC) " )
		
		//Present Swapchain
		VkPresentInfoKHR presentInfo {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.pNext = nullptr;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &_swapManager._swapchain;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &_renderFinishedSemaphore;
		presentInfo.pImageIndices = &imageIndex;
		presentInfo.pResults = nullptr;

		vkQueuePresentKHR( _queueManager.getPresentQueueHandler(), &presentInfo );
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	RenderDrawer::createSyncObjects() noexcept
	{
		VkSemaphoreCreateInfo sempahoreInfo {};
		sempahoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	
		VkFenceCreateInfo fenceInfo {};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		VkResult result = vkCreateSemaphore( _ownerDevice, &sempahoreInfo, nullptr, &_imageReadySemaphore);
		ASSERT( (result==VK_SUCCESS), "Error creating sync object semaphore 1 (:vC) " )

		result = vkCreateSemaphore( _ownerDevice, &sempahoreInfo, nullptr, &_renderFinishedSemaphore);
		ASSERT( (result==VK_SUCCESS), "Error creating sync object semaphore 2 (:vC) " )

		result = vkCreateFence( _ownerDevice, &fenceInfo, nullptr, &_frameRenderedFence );
		ASSERT( (result==VK_SUCCESS), "Error creating sync object fence (:vC) " )

	}


}