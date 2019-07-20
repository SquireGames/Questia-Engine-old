
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <GLFW/glfw3.h>
#include "QENG/graphics/Window.h"
#include "QENG/graphics/impl/opengl/GraphicsAPIImpl.h"
#include "QENG/graphics/GraphicsAPI.h"
#include "QENG/graphics/TextureManager.h"
#include "QENG/ClientEngine.h"
#include "QENG/math/FixedVector.h"

// Job based updates
// command queue for rendering, other thread

void render(const float percentToNextUpdate){}

constexpr unsigned int calculateTicksInNextUpdate(const unsigned int previousTicks, const unsigned int ticksPerSecond
                                      , const unsigned int nthUpdate, const unsigned int updatesPerSecond)
{
	// calculate the tick value is closest to the ideal value in the current progression
	auto idealTicksInPool = (unsigned int) (((float) nthUpdate / (float) updatesPerSecond) * (float) ticksPerSecond);
	// find how many ticks are required to reach the ideal amount
	return idealTicksInPool - previousTicks;
}

int main(int argc, char** argv)
{
	qe::GraphicsAPI api {std::make_unique<qe::gl::GraphicsAPIImpl>()};

	auto monitor = api.getPrimaryMonitor();

	qe::WindowOptions wo (qe::VideoMode(300, 300), qe::WindowOptions::Windowed());
	qe::Window window("Sample game application", wo, monitor);

	auto textureManager = qe::TextureManager();

	const unsigned int updatesPerSecond = 60;

	auto currentTime = std::chrono::duration_cast<std::chrono::duration<long, std::micro>>(std::chrono::high_resolution_clock::now().time_since_epoch());
	auto timePerFrame = std::chrono::duration<long, std::micro>(1'000'000/updatesPerSecond);

	auto timeAccumulator = std::chrono::duration<long, std::micro>(0);
	auto totalTimePassed = std::chrono::duration<long, std::micro>(0);

	// a tick pool allows every frame rate/update rate (e.g. 60fps, 100fps) to have the same amount of 'ticks' per second
	const unsigned int ticksPerSecond = 1000;
	unsigned int tickPoolProgress = 0;
	unsigned int nthUpdate = 0;

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
			// this is  useful for ensuring deterministic timesteps
			if(std::chrono::duration_cast<std::chrono::seconds>(oldTime) != std::chrono::duration_cast<std::chrono::seconds>(totalTimePassed))
			{
				// finish whats left of the tickBucket
				ticks = calculateTicksInNextUpdate(tickPoolProgress, ticksPerSecond, nthUpdate + 1, updatesPerSecond);

				// TODO remove begin
				tickPoolProgress += ticks;
				std::cout << std::to_string(tickPoolProgress) << std::endl;
				// TODO remove end

				//empty out the tick bucket
				tickPoolProgress = 0;
				nthUpdate = 0;

				std::cout << std::to_string(totalTimePassed.count()) << std::endl;
			}
			else
			{
				ticks = calculateTicksInNextUpdate(tickPoolProgress, ticksPerSecond, (nthUpdate += 1), updatesPerSecond);
				tickPoolProgress += ticks;
				std::cout << std::to_string(tickPoolProgress) << std::endl;
			}

			api.pollEvents();
		}

		const float percentToNextUpdate = timeAccumulator / timePerFrame;

		render(percentToNextUpdate);
	}

	return 0;
}
