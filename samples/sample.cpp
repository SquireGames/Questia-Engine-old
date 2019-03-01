
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <QENG/graphics/opengl/GLInstance.h>
#include <QENG/graphics/GraphicsAPI.h>
#include <QENG/math/Vector2.h>
#include "QENG/ClientEngine.h"
#include "QENG/math/FixedVector.h"

int main(int argc, char** argv)
{
	{
		auto a = FixedVector<int, 3>{5, 7, 11};
		std::cout << std::to_string(a.get<0>()) << std::endl;
		std::cout << std::to_string(a[1]) << std::endl;

		auto b = FixedVector<int, 3>{7, 11, 2};
		std::cout << std::to_string(a == b) << std::endl;
	}

	qe::GraphicsAPI api {std::make_unique<qe::GLInstance>()};

	auto monitors = api.getMonitors();
	for (auto& monitor : monitors)
	{
		std::cout << monitor.getMonitorName() << std::endl;
	}

	qe::Vector2i test {1, 3};
	std::cout << std::to_string(test.x) << std::endl;
	std::cout << std::to_string(test.y) << std::endl;

	qe::Vector2f a = test.normalize<float>();
	std::cout << std::to_string(a.x);

	//qe::ClientEngine engine;
	//engine.run();

	return 0;
}
