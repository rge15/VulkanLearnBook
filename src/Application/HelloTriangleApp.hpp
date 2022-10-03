#include "../engine/VEngine.hpp"
#include "../utilities/assertMacros.hpp"


class HelloTriangleApp
{
	private:
		Graphics::VEngine engine{};

		void initEngine() noexcept;

		void mainLoop() noexcept;

		void cleanUp() noexcept;

	public:
		HelloTriangleApp(/* args */);
		~HelloTriangleApp();

		void runApp() noexcept;
};