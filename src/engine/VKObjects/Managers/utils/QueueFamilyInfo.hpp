#pragma once
#include <utilities/config.hpp>

namespace Graphics::Manager
{
	struct QueueFamilyInfo{
		std::optional<uint32_t> _graphicsFamilyQueueIndex;
		float _priorityValue { 0.f };

		bool isComplete() const noexcept;
	};
}