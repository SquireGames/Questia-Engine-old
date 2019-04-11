
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <GLFW/glfw3.h>
#include "QENG/graphics/opengl/GLInstance.h"
#include "QENG/graphics/GraphicsAPI.h"
#include "QENG/ClientEngine.h"
#include "QENG/math/FixedVector.h"

int main(int argc, char** argv)
{
	qe::GraphicsAPI api {std::make_unique<qe::GLInstance>()};

	auto monitorCallback = [](const qe::Monitor& m, qe::Monitor::State s)
	{
		switch(s)
		{
			case qe::Monitor::State::connected:     std::cout << "Connected " << m.getName() << std::endl; break;
			case qe::Monitor::State::disconnected:  std::cout << "Disconnected " << m.getName()  << std::endl; break;
		}
	};

	auto monitors = api.getMonitors();
	for (auto& monitor : monitors)
	{
		std::cout << monitor.getName() << std::endl;
		std::cout << "Position: " << std::to_string(monitor.getPosition().x()) << ", " << std::to_string(monitor.getPosition().y()) << std::endl;
		std::cout << "Physical Size: " << std::to_string(monitor.getPhysicalSize().x()) << ", " << std::to_string(monitor.getPhysicalSize().y()) << std::endl;
		monitor.setMonitorCallback(monitorCallback);
		std::cout << std::endl;
	}

	while(1)
	{
		glfwPollEvents();
	}
	return 0;
}
