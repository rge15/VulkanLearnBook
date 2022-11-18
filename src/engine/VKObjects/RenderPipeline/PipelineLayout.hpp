#pragma once
#include <utilities/graphicsInclude.hpp>
#include <utilities/TypeAliases.hpp>
#include <utilities/assertMacros.hpp> 

namespace Graphics
{
	class PipelineLayout
	{
	private:
		VkDevice& _device;
	
		VkPipelineLayoutCreateInfo _layoutCreateInfo {};
	
		void
		initPipelineLayoutData() noexcept;

		void
		createPipelineLayout() noexcept;
	public:
		VkPipelineLayout _layout;

	public:
		PipelineLayout( VkDevice& p_device ) noexcept;
		
		~PipelineLayout() noexcept;
	};

}