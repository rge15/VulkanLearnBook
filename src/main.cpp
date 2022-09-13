#include "engine/VEngine.hpp"
#include "utilities/assertMacros.hpp"

int main()
{
	Graphics::VEngine engine{};

	GLFWwindow& wind = engine.getWindow();

	while(!glfwWindowShouldClose(&wind))
	{
		glfwPollEvents();
	}

	return 0;
}