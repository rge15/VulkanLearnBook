#include "QueueFamilyInfo.hpp"

namespace Graphics::Manager
{
	bool
	QueueFamilyInfo::isComplete() const noexcept
	{
		if( _graphicsFamilyQueueIndex.has_value() )
			return true;
		return false;
	}
}