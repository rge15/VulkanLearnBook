#include "HelloTriangleApp.hpp"

HelloTriangleApp::HelloTriangleApp()
{
}

HelloTriangleApp::~HelloTriangleApp()
{
}

void HelloTriangleApp::initEngine() noexcept
{
}

void HelloTriangleApp::mainLoop() noexcept{

	auto& wind = engine.getWindow();

	engine._VResourceMngr.get()->loadGraphicResource<VShader>("src/Application/shaders/vert.sprv", VShader::ShaderType::VK_SHADER_STAGE_VERTEX_BIT );

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