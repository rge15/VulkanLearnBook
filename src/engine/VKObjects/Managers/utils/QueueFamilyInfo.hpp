#pragma once
#include <utilities/config.hpp>
#include <utilities/assertMacros.hpp>
#include <vulkan/vulkan.h>
#include "../queueIndex/GraphicsQueueIndex.hpp"
#include "../queueIndex/PresentQueueIndex.hpp"

namespace Graphics::Manager
{
	struct QueueFamilyInfo{
		GraphicsQueueIndex _graphicsFamilyQueueIndex;
		PresentQueueIndex _presentFamilyQueueIndex;

		std::vector<uint32_t> _queuesIds {};
		
		float _priorityValue { 1.f };


		/**
		 *	@brief Check if the Queue Family IDs are all filled or not
		 *
		 *	@return Returns True if all the IDs are filled
		*/
		bool
		isComplete() const noexcept;

		/**
		 * 	@brief Selects the best physical device that best fits the requeriments
		 * 
		 * 	@param p_queueProp Reference to the vector of queue family properties to check with 
		 * 	@param p_surface Surface to present in and to check the requeriments
		 * 	@param p_device Physical device that manages the surface
		*/
		void
		pickBestPhysicalDeviceQueues(
			const std::vector<VkQueueFamilyProperties>& p_queueProp,
			const VkSurfaceKHR& p_surface,
			const VkPhysicalDevice& p_device
		) noexcept;

		/**
		 * @brief Fill a std::set with the queues IDs
		 * 
		 * @param p_set Set to fill the data in
		*/
		void
		getSetIndex(std::set<uint32_t>& p_set) const noexcept;

		private:

		/**
		 * @brief Checks the queue managers for each Queue Family Properties
		 * 		for picking the best physical device
		 * 
		 * 	@param p_queueProp Reference to the vector of queue family properties to check with 
		 * 	@param p_queueId Id of the queue being checked
		 * 	@param p_surface Surface to present in and to check the requeriments
		 * 	@param p_device Physical device that manages the surface
		*/
		void
		checkAllQueueManagers(
			const VkQueueFamilyProperties& p_prop,
			const int& p_queueId,
			const VkSurfaceKHR& p_surface,
			const VkPhysicalDevice& p_device
		) noexcept;

		/**
		 * 	@brief Cleans all the queue ID managers
		*/
		void
		clean() noexcept;

	};
}