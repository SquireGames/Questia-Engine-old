
#include <iostream>
#include <chrono>
#include <thread>
#include "QENG/ClientEngine.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

int main(int argc, char** argv)
{
	qe::ClientEngine engine;
	engine.run();

	return 0;
}
