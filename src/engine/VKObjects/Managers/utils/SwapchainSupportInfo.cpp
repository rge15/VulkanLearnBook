#include "SwapchainSupportInfo.hpp"


void
SwapchainSupportInfo::clean() noexcept
{
	_formats.clear();
	_formats.shrink_to_fit();
	_presentModes.clear();
	_presentModes.shrink_to_fit();
}