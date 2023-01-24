#pragma once
#include <utilities/graphicsInclude.hpp>
#include <engine/VKObjects/Managers/SwapchainManager.hpp>
#include <engine/VKObjects/Managers/QueueManager.hpp>
#include <engine/VKObjects/RenderPipeline/RenderPipeline.hpp>

namespace Graphics
{

    class RenderDrawer
    {
    private:
		VkDevice& _ownerDevice;
		Manager::SwapchainManager& _swapManager;
		Manager::QueueManager& _queueManager;
        RenderPipeline& _renderPipeline;
        Vector<VkFramebuffer>& _frameBuffers;

        VkCommandPool _cmdPool { VK_NULL_HANDLE };
        VkCommandBuffer _cmdBuffer { VK_NULL_HANDLE };

        VkSemaphore _imageReadySemaphore        { VK_NULL_HANDLE };
        VkSemaphore _renderFinishedSemaphore    { VK_NULL_HANDLE };
        VkFence     _frameRenderedFence         { VK_NULL_HANDLE };

    public:
        RenderDrawer(
			VkDevice& p_device, 
			Manager::SwapchainManager& p_swapchainManager,
			Manager::QueueManager& p_queueManager,
            RenderPipeline& p_renderPipeline,
            Vector<VkFramebuffer>& p_frameBuffers
        ) noexcept;

        ~RenderDrawer() noexcept;

        void
        draw() noexcept;

    private:
        
        void
        reserveCommandPool() noexcept;

        void
        allocateCommandBuffer() noexcept;

        void
        beginRecordCmdBuffer() noexcept;

        void
        renderPass( const int32_t p_imageIndex ) noexcept;

    	void
    	endRecordCmdBuffer() noexcept;

        void
        recordDrawCommand( const int32_t p_imageIndex) noexcept;

    	void
    	createSyncObjects() noexcept;

    };
    
}