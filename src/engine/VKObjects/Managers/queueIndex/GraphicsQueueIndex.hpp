#pragma once
#include "QueueIndexManager.hpp"
#include <vulkan/vulkan.h>

namespace Graphics::Manager
{
	class GraphicsQueueIndex : public QueueIndexManager
	{
	public:
		/** @brief Default constructor of class GraphicsQueueIndex */
		GraphicsQueueIndex() = default;

		/** @brief Default destructor of class GraphicsQueueIndex */
		~GraphicsQueueIndex() = default;

		/**
		 * 	@brief Check if the passed queue family properties
		 * 			satisfies the requeriments to be the graphics queue
		 * 
		 * 	@param p_prop Reference to the queue family properties to check
		 * 	@param p_queueId ID of the queue being checked
		*/
		void
		checkQueueGraphicsProperties(
			const VkQueueFamilyProperties& p_prop,
			const int& p_queueId
		) noexcept;

	};
	
}