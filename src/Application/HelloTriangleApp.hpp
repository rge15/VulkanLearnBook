#include "../engine/VEngine.hpp"
#include "App.hpp"

class HelloTriangleApp : public App
{
	private:
		Graphics::VEngine engine{};

		void initEngine() noexcept;

		void mainLoop() noexcept;

		void cleanUp() noexcept;

	public:
		HelloTriangleApp(/* args */);
		~HelloTriangleApp();

		void runApp() noexcept override final;
};