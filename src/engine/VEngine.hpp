#include "../utilities/config.hpp"
#include "../utilities/assertMacros.hpp"
#include "VDriver.hpp"

namespace Graphics
{
	class VEngine
	{
	private:

		//UniquPtr for the Driver Manager of the Engine
		std::unique_ptr<VDriver> _VDriver { nullptr };

	public:
		
		/**
		*	@brief Default contructor for VEngine Class
		*	
		*	@param p_w Width for the screen size. Default = 640
		*	@param p_h Height for the screen size. Default = 640
		*/
		VEngine( const uint32_t p_w = 640, const uint32_t p_h = 480 ) noexcept;

		/**
		 * 	@brief Default destructor for VEngine Class
		*/
		~VEngine() noexcept;

		/**
		 * 	@brief Get the window created by the Engine
		 * 
		 * 	@return Reference to the created window
		*/
		GLFWwindow& getWindow() const noexcept;

	};
}