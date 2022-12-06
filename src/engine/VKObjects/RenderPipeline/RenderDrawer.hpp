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
		const Manager::SwapchainManager& _swapManager;
		const Manager::QueueManager& _queueManager;
        RenderPipeline& _renderPipeline;
        Vector<VkFramebuffer>& _frameBuffers;

        VkCommandPool _cmdPool { VK_NULL_HANDLE };
        VkCommandBuffer _cmdBuffer { VK_NULL_HANDLE };


    public:
        RenderDrawer(
			VkDevice& p_device, 
			const Manager::SwapchainManager& p_swapchainManager,
			const Manager::QueueManager& p_queueManager,
            RenderPipeline& p_renderPipeline,
            Vector<VkFramebuffer>& p_frameBuffers
        ) noexcept;

        ~RenderDrawer() noexcept;

        void
        recordDrawCommand( const int32_t p_imageIndex) noexcept;

    private:
        
        void
        reserveCommandPool() noexcept;

        void
        allocateCommandBuffer() noexcept;

        void
        beginCmdBuffer() noexcept;

        void
        renderPass( const int32_t p_imageIndex ) noexcept;

    	void
    	endCmdBuffer() noexcept;

    };
    
}