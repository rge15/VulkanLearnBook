#pragma once
#include "QueueIndexManager.hpp"
#include <vulkan/vulkan.h>

namespace Graphics::Manager
{
	class PresentQueueIndex : public QueueIndexManager
	{
	public:
		/** @brief Default constructor of class PresentQueueIndex */
		PresentQueueIndex() = default;
		
		/** @brief Default destructor of class PresentQueueIndex */
		~PresentQueueIndex() = default;

		/**
		 * 	@brief Check if the passed queue family properties
		 * 			satisfies the requeriments to be the graphics queue
		 * 
		 * 	@param p_prop Reference to the queue family properties to check
		 * 	@param p_queueId ID of the queue being checked
		 * 	@param p_surface Surface to check if can be presented to
		 * 	@param p_device Physical device that owns the surface
		*/
		void
		checkQueuePresentProperties(
			const VkQueueFamilyProperties& p_prop,
			const int& p_queueId,
			const VkSurfaceKHR& p_surface,
			const VkPhysicalDevice& p_device			
		) noexcept;

	};
	
}