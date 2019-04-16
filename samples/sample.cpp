
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <GLFW/glfw3.h>
#include <QENG/graphics/Window.h>
#include "QENG/graphics/opengl/GLInstance.h"
#include "QENG/graphics/GraphicsAPI.h"
#include "QENG/ClientEngine.h"
#include "QENG/math/FixedVector.h"

int main(int argc, char** argv)
{
	qe::GraphicsAPI api {std::make_unique<qe::GLInstance>()};

	auto monitor = api.getPrimaryMonitor();

	qe::Window window ("Window", 100, 200, monitor);

	auto a = window.getWidth();
	std::cout << std::to_string(a) << std::endl;

	while(1)
	{
		glfwPollEvents();
	}
	return 0;
}
