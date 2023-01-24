#include "VRenderManager.hpp"

namespace Graphics
{

	VRenderManager::VRenderManager( 
		VkDevice& p_device,
		Manager::SwapchainManager& p_swapManager,
		Manager::QueueManager& p_queueManager
	) noexcept
	: _swapManager { p_swapManager }
	, _ownerDevice { p_device }
	, _queueManager { p_queueManager }
	, _pipelineLayout { std::make_unique<PipelineLayout>( p_device ) }
	, _renderPass { std::make_unique<RenderPass>( p_device, p_swapManager.getSwapchainInfo() ) }
	{
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	VRenderManager::~VRenderManager()
	{
		for(auto i = 0 ; i < _swapchainFramebuffers.size(); i++)
		{
			vkDestroyFramebuffer( _ownerDevice, _swapchainFramebuffers[i], nullptr);
		}
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	VRenderManager::addPipelineShaderStages( VkPipelineShaderStageCreateInfo& p_shader ) noexcept
	{
		_pipelineShaders.push_back( p_shader );
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	VRenderManager::createRenderPipeline() noexcept
	{
		_renderPipeline = std::make_unique<RenderPipeline>( 
			_ownerDevice,
			_pipelineLayout.get()->_layout, 
			_renderPass.get()->_renderPass,
			_swapManager.getSwapchainInfo() );

		_renderPipeline.get()->setShaderStages( _pipelineShaders );
		_renderPipeline.get()->createPipeline();
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	VRenderManager::setUpRenderPipeline() noexcept
	{
		if( _renderPipeline == nullptr )
		{
			createRenderPipeline();
			createFrameBuffers();
		}else
			std::cout << "Render Pipeline already setted (;vD)" << '\n';
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	VRenderManager::createFrameBuffers() noexcept
	{
		auto& swapImageViews = _swapManager.getImageViews();
		auto& swapInfo = _swapManager.getSwapchainInfo();
		_swapchainFramebuffers.resize( swapImageViews.size() );

		int i = 0;
		for(auto& imageView : swapImageViews)
		{
			VkImageView imageViewArray[] = { imageView };

			VkFramebufferCreateInfo frameCreateInfo {};
			frameCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			frameCreateInfo.pNext = nullptr;
			frameCreateInfo.attachmentCount = 1;
			frameCreateInfo.pAttachments = imageViewArray;
			frameCreateInfo.renderPass = _renderPass.get()->_renderPass;
			frameCreateInfo.height = swapInfo._swapchainExtent.height;
			frameCreateInfo.width = swapInfo._swapchainExtent.width;
			frameCreateInfo.layers = 1;
			frameCreateInfo.flags = 0;

			auto result = vkCreateFramebuffer( _ownerDevice, &frameCreateInfo, nullptr, &_swapchainFramebuffers[i] );

			ASSERT( (result == VK_SUCCESS), "Error creating a framebuffer from the swapchain" );
		
			std::cout << "Framebuffer[" << i << "] succesfully created :D" << std::endl;

			++i;
		}

	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	VRenderManager::prepareRenderPipelineDrawing() noexcept
	{
		if(_renderPipeline.get() == nullptr)
		{
			std::cout << "Render Pipeline isn't created (:vC), call setUpRenderPipeline() before setting your shaderStages." << '\n';
			return;
		}

		if(_renderDrawer.get() == nullptr)
			_renderDrawer = std::make_unique<RenderDrawer>(_ownerDevice, _swapManager, _queueManager, *_renderPipeline.get(), _swapchainFramebuffers);
		else
			std::cout << "Render Drawer already setted (;vD)" << '\n';

	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	RenderDrawer* const
	VRenderManager::getDrawer() const noexcept
	{

		if(_renderDrawer.get() != nullptr)
			return _renderDrawer.get();
		
		std::cout << "Render Drawer is not setted (:vc)" << '\n';
		return nullptr;
	};


}