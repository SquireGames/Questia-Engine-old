
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <QENG/graphics/opengl/GLInstance.h>
#include <QENG/graphics/GraphicsAPI.h>
#include <QENG/math/Vector2.h>
#include "QENG/ClientEngine.h"

int main(int argc, char** argv)
{
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
