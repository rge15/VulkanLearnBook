#include "PipelineLayout.hpp"

namespace Graphics
{

PipelineLayout::PipelineLayout( VkDevice& p_device) noexcept
: _device { p_device }
{
	initPipelineLayoutData();
	createPipelineLayout();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

PipelineLayout::~PipelineLayout() noexcept
{
	vkDestroyPipelineLayout(_device, _layout, nullptr);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
PipelineLayout::initPipelineLayoutData() noexcept
{
	_layoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	_layoutCreateInfo.pNext = nullptr;
	_layoutCreateInfo.flags = 0;
	
	//Right now this will be empty
	_layoutCreateInfo.setLayoutCount = 0;
	_layoutCreateInfo.pSetLayouts = nullptr;

	_layoutCreateInfo.pushConstantRangeCount = 0;
	_layoutCreateInfo.pPushConstantRanges = 0;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
PipelineLayout::createPipelineLayout() noexcept
{	
	VkResult result = vkCreatePipelineLayout(_device, &_layoutCreateInfo, nullptr, &_layout);

	ASSERT( (result == VK_SUCCESS), "Failed in creation of pipeline layout" ) 
}

}
