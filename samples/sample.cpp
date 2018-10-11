
#include <iostream>
#include <chrono>
#include <thread>
#include "QENG/ClientEngine.h"

int main(int argc, char** argv)
{
	qe::ClientEngine engine;
	engine.run();

	return 0;
}
