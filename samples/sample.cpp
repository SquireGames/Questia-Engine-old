
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <GLFW/glfw3.h>
#include <QENG/graphics/Window.h>
#include "QENG/graphics/impl/opengl/GraphicsAPIImpl.h"
#include "QENG/graphics/GraphicsAPI.h"
#include "QENG/graphics/TextureManager.h"
#include "QENG/ClientEngine.h"
#include "QENG/math/FixedVector.h"

// Job based updates
// command queue for rendering, other thread

void render(const float percentToNextUpdate){}

int main(int argc, char** argv)
{
	qe::GraphicsAPI api {std::make_unique<qe::gl::GraphicsAPIImpl>()};

	auto monitor = api.getPrimaryMonitor();

	qe::WindowOptions wo (qe::VideoMode(300, 300), qe::WindowOptions::Windowed());
	qe::Window window("Sample game application", wo, monitor);

	auto textureManager = qe::TextureManager();

	const int updatesPerSecond = 60;

	auto currentTime = std::chrono::duration_cast<std::chrono::duration<long, std::micro>>(std::chrono::high_resolution_clock::now().time_since_epoch());
	auto timePerFrame = std::chrono::duration<long, std::micro>(1'000'000/updatesPerSecond);

	auto timeAccumulator = std::chrono::duration<long, std::micro>(0);
	auto totalTimePassed = std::chrono::duration<long, std::micro>(0);

	// every second, this will be emptied into the update function.
	// this allows every tick rate (e.g. 60fps, 100fps) to have the same amount of 'ticks' per second
	unsigned int tickPool = 1000;

	while(!window.shouldClose())
	{
		auto newTime = std::chrono::duration_cast<std::chrono::duration<long, std::micro>>(std::chrono::high_resolution_clock::now().time_since_epoch());
		auto frameTime = newTime - currentTime;
		currentTime = newTime;

		timeAccumulator += frameTime;


		// TODO correct for time drift, simplest solution being to use modulo to find the difference and add a modifier onto timePerFrame
		while(timeAccumulator >= timePerFrame)
		{
			const auto oldTime = totalTimePassed;
			totalTimePassed += timePerFrame;
			timeAccumulator -= timePerFrame;

			unsigned int ticks;

			// every time a second passes, NOTE this will only work when the tick rate is greater than or equal to once per second
			// this is very useful for ensuring deterministic timesteps
			if(std::chrono::duration_cast<std::chrono::seconds>(oldTime) != std::chrono::duration_cast<std::chrono::seconds>(totalTimePassed))
			{
				// empty out the rest of the tickPool into ticks
				ticks = tickPool;
				tickPool = 1000;
				std::cout << std::to_string(totalTimePassed.count()) << std::endl;
			}
			else
			{
				ticks = updatesPerSecond / 1000;
			}

			api.pollEvents();
		}

		const float percentToNextUpdate = timeAccumulator / timePerFrame;

		render(percentToNextUpdate);
	}

	return 0;
}
