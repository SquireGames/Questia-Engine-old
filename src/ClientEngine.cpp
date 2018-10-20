#include <iostream>
#include "QENG/ClientEngine.h"

namespace qe
{
	qe::ClientEngine::ClientEngine(qe::EngineSettings initSettings) noexcept :
			graphicsInstance(),
			window(),
			frameRate(initSettings.frameRate),
			tickRate(initSettings.tickRate),
			tickCount(0)
	{
		window = std::unique_ptr<Window>(new Window(u8"Questia Engine game title", initSettings.screenWidth, initSettings.screenHeight));
	}

	void ClientEngine::run() noexcept
	{
		while(!window->isClosed())
		{
			window->update();
		}
		/*

		 */
	}

	void ClientEngine::setTickRate(unsigned int tickRate) noexcept
	{
		this->tickRate = tickRate;
	}

	void ClientEngine::setFrameRate(unsigned int frameRate) noexcept
	{
		this->frameRate = frameRate;
	}

	unsigned int ClientEngine::getTickRate() const noexcept
	{
		return tickRate;
	}

	unsigned int ClientEngine::getFrameRate() const noexcept
	{
		return frameRate;
	}
}
