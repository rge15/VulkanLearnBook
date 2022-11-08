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
	
		VkPipelineLayout _layout;
		VkPipelineLayoutCreateInfo _layoutCreateInfo {};

		void
		initPipelineLayoutData() noexcept;

		void
		createPipelineLayout() noexcept;

	public:
		PipelineLayout( VkDevice& p_device ) noexcept;
		
		~PipelineLayout() noexcept;
	};

}