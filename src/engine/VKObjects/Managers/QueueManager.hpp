#pragma once
#include <utilities/config.hpp>
#include <vulkan/vulkan.h>
#include "utils/QueueFamilyInfo.hpp"
#include "../Helpers/GetVKObjects.hpp"

namespace Graphics::Manager
{
	class QueueManager
	{
		private:
			std::vector<VkDeviceQueueCreateInfo> _queueInfo	{};
			QueueFamilyInfo _queueIndexInfo	{};
			VkQueue			_presentQueueHandler	{};
			VkQueue			_graphicsQueueHandler	{};


		public:
			/** @brief Default constructor for QueueManager class */
			QueueManager() noexcept = default;

			/** @brief Default destructor for QueueManager class */
			~QueueManager() noexcept = default;

			/**
			 * 	@brief Checks if the passed device and surface suits the _queueIndexInfo requeriments
			 * 
			 * 	@param p_device Physical device to check with
			 * 	@param p_surface Surface to check with
			 * 
			 * 	@return True if the passed data suits correctly
			*/
			bool 
			checkQueuesSuitability( VkPhysicalDevice& p_device, VkSurfaceKHR& p_surface ) noexcept;

			/**
			 * 	@brief Inits the creation queue information
			*/
			void 
			initQueueCreateInfo() noexcept;

			/**
			 * 	@brief Return the number of queues that this queue manager handles
			 * 
			 * 	@return Number of queues that handles
			*/
			int32_t
			getQueueCount() noexcept { return _queueInfo.size(); }

			/**
			 * 	@brief Return the number of queues that this queue manager handles
			 * 
			 * 	@return Number of queues that handles
			*/
			VkDeviceQueueCreateInfo*
			getQueueData() noexcept { return _queueInfo.data(); }

			/**
			 * 	@brief Return the reference to the queueFamilyInfo
			 * 
			 * 	@return Reference to the queue family info
			*/
			QueueFamilyInfo&
			getQueueFamilyInfo() noexcept { return _queueIndexInfo; }

			/**
			 * 	@brief Sets the queue handler for the Graphic queue management to the passed queue handler reference
			 * 
			 * 	@param p_device Vulkan Device to get the queue handler from
			 * 	@param p_queueHandler VUlkan queue to set the queue handler in
			*/
			void
			setGraphicHandler( VkDevice& p_device ) noexcept;

			/**
			 * 	@brief Sets the queue handler for the Present queue management to the passed queue handler reference
			 * 
			 * 	@param p_device Vulkan Device to get the queue handler from
			 * 	@param p_queueHandler Vulkan queue to set the queue handler in
			*/
			void
			setPresentHandler( VkDevice& p_device ) noexcept;

			/**
			 * 	@brief Update the queues data IDs
			*/
			void
			updateQueueIdData() noexcept;

			/**
			 * 	@brief Gets the Graphic queue ID
			*/
			int
			getGraphicQueueId() const noexcept;

			/**
			 * 	@brief Gets the Present queue ID
			*/
			int
			getPresentQueueId() const noexcept;

			VkQueue&
			getGraphicQueueHandler() noexcept;

			VkQueue&
			getPresentQueueHandler() noexcept;


	};
}