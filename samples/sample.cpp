
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <QENG/graphics/opengl/GLInstance.h>
#include "QENG/ClientEngine.h"

int main(int argc, char** argv)
{
	std::unique_ptr<qe::GraphicsAPI> api {new qe::GLInstance()};

	std::vector<qe::Monitor*> monitors = api->getMonitors();



	//qe::ClientEngine engine;
	//engine.run();

	return 0;
}
