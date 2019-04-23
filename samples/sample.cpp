
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

	std::cout << monitor.getName() << std::endl;
	std::cout << std::to_string(monitor.getVideoMode().redBits) << std::endl;

	qe::Window window("Window", qe::WindowOptions(qe::VideoMode(100, 100), qe::WindowOptions::Fullscreen()), monitor);

	auto a = window.getWidth();
	std::cout << std::to_string(a) << std::endl;

	while(1)
	{
		glfwPollEvents();
		break;
	}
	return 0;
}
