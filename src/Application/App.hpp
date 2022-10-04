#include "../utilities/assertMacros.hpp"

class App
{
	public:

		virtual ~App() = default;

		virtual void runApp() = 0; 
};