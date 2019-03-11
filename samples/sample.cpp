
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <QENG/graphics/opengl/GLInstance.h>
#include <QENG/graphics/GraphicsAPI.h>
#include "QENG/ClientEngine.h"
#include "QENG/math/FixedVector.h"

int main(int argc, char** argv)
{
	auto a = qe::FixedVector<int, 3>{5, 7, 11};
	std::cout << std::to_string(a.get<0>()) << std::endl;
	std::cout << std::to_string(a[1]) << std::endl;

	auto b = qe::FixedVector<int, 3>{7, 11, 2};
	std::cout << std::to_string(a == b) << std::endl;

	qe::GraphicsAPI api {std::make_unique<qe::GLInstance>()};

	auto monitors = api.getMonitors();
	for (auto& monitor : monitors)
	{
		std::cout << monitor.getMonitorName() << std::endl;
	}

	return 0;
}
