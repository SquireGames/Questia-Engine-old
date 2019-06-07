
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <GLFW/glfw3.h>
#include <QENG/graphics/Window.h>
#include "QENG/graphics/impl/opengl/GraphicsAPI.h"
#include "QENG/graphics/GraphicsAPI.h"
#include "QENG/ClientEngine.h"
#include "QENG/math/FixedVector.h"

int main(int argc, char** argv)
{
	qe::GraphicsAPI api {std::make_unique<qe::gl::GraphicsAPI>()};

	auto monitor = api.getPrimaryMonitor();

	qe::WindowOptions wo (qe::VideoMode(300, 300), qe::WindowOptions::Windowed());
	qe::Window window("Window", wo, monitor);

	while(!window.shouldClose())
	{
		api.pollEvents();
	}

	return 0;
}
