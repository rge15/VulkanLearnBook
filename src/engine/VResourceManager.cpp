#include "VResourceManager.hpp"

namespace Graphics
{
	
	VResourceManager::VResourceManager( VkDevice& p_deviceOwner ) noexcept
	: _device { p_deviceOwner }
	{
	}

}