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

	auto& window = engine.getWindow();
	auto& resourceMngr = *engine._VResourceMngr.get();
	auto& renderMngr = *engine._VRenderMngr.get();

	auto [ fShaderID, vertexShader ] = resourceMngr.loadGraphicResource<VShader>("src/Application/shaders/vert.sprv", VShader::ShaderType::VK_SHADER_STAGE_VERTEX_BIT );
	auto [ vShaderID, fragmentShader ] = resourceMngr.loadGraphicResource<VShader>("src/Application/shaders/frag.sprv", VShader::ShaderType::VK_SHADER_STAGE_FRAGMENT_BIT );

	renderMngr.addPipelineShaderStages( vertexShader._stageInfo );
	renderMngr.addPipelineShaderStages( fragmentShader._stageInfo );
	renderMngr.setUpRenderPipeline();

	renderMngr.prepareRenderPipelineDrawing();

	while(!glfwWindowShouldClose(&window))
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