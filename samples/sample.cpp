
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

		// make sure to set gamma back to original after closing program!
		// auto b = monitor.setGamma(1);
		// std::cout << std::to_string(b) << std::endl;

		auto videoModes = monitor.getVideoModes();
		for(auto mode : videoModes)
		{
			std::cout << std::to_string(mode.width) << "," <<  std::to_string(mode.height) << ","  << std::to_string(mode.redBits) << ","
					<< std::to_string(mode.greenBits) << "," << std::to_string(mode.blueBits) << ","  << std::to_string(mode.refreshRate) << std::endl;
		}
		auto currentMode = monitor.getVideoMode();
		std::cout << "Current: " << std::to_string(currentMode.width) << "," <<  std::to_string(currentMode.height) << ","  << std::to_string(currentMode.redBits) << ","
		          << std::to_string(currentMode.greenBits) << "," << std::to_string(currentMode.blueBits) << ","  << std::to_string(currentMode.refreshRate) << std::endl;

		monitor.setMonitorCallback(monitorCallback);
		std::cout << std::endl;
	}

	while(1)
	{
		glfwPollEvents();
	}
	return 0;
}
