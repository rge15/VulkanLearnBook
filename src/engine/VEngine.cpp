#include "VEngine.hpp"

//TODO : A ver crack, antes de ponerte a seguir con los videos mira bien que es una instance
//TODO : de vulkan y una vez lo sepas intenta estructurar un poco el código. Esto pa mañana <3 

VEngine::VEngine( const uint32_t p_w, const uint32_t p_h ) noexcept :
_VDriver { std::make_unique<VDriver>(p_w,p_h) }
{
}

VEngine::~VEngine() noexcept
{
}

GLFWwindow&
VEngine::getWindow() const noexcept
{
	assert(_VDriver.get());
	return *_VDriver.get()->getWindow();
}
