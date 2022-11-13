#include "RenderPass.hpp"

namespace Graphics
{

	RenderPass::RenderPass(const Manager::SwapchainInfo& p_swapInfo) noexcept
	: _swapchainInfo { p_swapInfo }
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

	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	RenderPass::initInfo() noexcept
	{

	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	RenderPass::createRenderPass() noexcept
	{

	}


}