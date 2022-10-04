#include "Application/HelloTriangleApp.hpp"

int main()
{
	std::unique_ptr<App> app = std::make_unique<HelloTriangleApp>();

	app.get()->runApp();

	return 0;
}