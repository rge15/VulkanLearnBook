#include "../utilities/config.hpp"
#include "../utilities/assertMacros.hpp"
#include "VDriver.hpp"
class VEngine
{
private:

	std::unique_ptr<VDriver> _VDriver { nullptr };

public:

	VEngine( const uint32_t p_w = 640, const uint32_t p_h = 480 ) noexcept;

	~VEngine() noexcept;

	GLFWwindow& getWindow() const noexcept;

};
