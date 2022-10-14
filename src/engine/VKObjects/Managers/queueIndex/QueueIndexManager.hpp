#pragma once
#include <utilities/config.hpp>


namespace Graphics::Manager
{
	class QueueIndexManager
	{
		protected:
			std::optional<uint32_t> _queueId;
		public:
			/** @brief Default constructor of class QueueIndexManager */
			QueueIndexManager() = default;

			/** @brief Default destructor of class QueueIndexManager */
			~QueueIndexManager() = default;

			/**
			 * 	@brief Check if the manager has a queue ID
			 * 
			 * 	@return bool with True if it contains a value 
			*/
			bool
			hasValue() const noexcept;

			/**
			 * 	@brief Gets the queue index manager value
			 * 
			 * 	@return uint32_t with the queue ID 
			*/
			uint32_t
			getValue() const noexcept;
	
			/**
			 * 	@brief Resets the value of the queue ID managed
			*/
			void
			reset() noexcept;
	
	};
}