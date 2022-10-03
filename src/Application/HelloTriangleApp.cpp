#include "HelloTriangleApp.hpp"

HelloTriangleApp::HelloTriangleApp()
{
}

HelloTriangleApp::~HelloTriangleApp()
{
}

void HelloTriangleApp::initEngine() noexcept{

}

void HelloTriangleApp::mainLoop() noexcept{

	auto& wind = engine.getWindow();

	while(!glfwWindowShouldClose(&wind))
	{
		glfwPollEvents();
	}

}

void HelloTriangleApp::cleanUp() noexcept{

}


void HelloTriangleApp::runApp() noexcept
{
	initEngine();
	mainLoop();
	cleanUp();
}