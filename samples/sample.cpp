
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <QENG/graphics/opengl/GLInstance.h>
#include <QENG/graphics/GraphicsAPI.h>
#include "QENG/ClientEngine.h"

int main(int argc, char** argv)
{
	qe::GraphicsAPI api {std::make_unique<qe::GLInstance>()};

	auto monitors = api.getMonitors();
	for (auto& monitor : monitors)
	{
		std::cout << monitor.getMonitorName() << std::endl;
	}

	//qe::ClientEngine engine;
	//engine.run();

	return 0;
}
