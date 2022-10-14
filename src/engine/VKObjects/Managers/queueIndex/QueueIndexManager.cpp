#include "QueueIndexManager.hpp"


namespace Graphics::Manager
{
	bool
	QueueIndexManager::hasValue() const noexcept
	{
		return _queueId.has_value();
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	uint32_t
	QueueIndexManager::getValue() const noexcept
	{
		return _queueId.value();
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	void
	QueueIndexManager::reset() noexcept
	{
		_queueId.reset();
	}
}