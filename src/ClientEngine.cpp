#include <iostream>
#include <QENG/graphics/impl/opengl/GraphicsAPI.h>
#include "QENG/ClientEngine.h"

namespace qe
{
	ClientEngine::ClientEngine(qe::EngineSettings initSettings) noexcept :
			renderer({new gl::GraphicsAPI()}),
			//window(),
			frameRate(initSettings.frameRate),
			tickRate(initSettings.tickRate),
			tickCount(0)
	{
	//	window = std::unique_ptr<Window>(new Window(u8"Questia Engine game title", initSettings.screenWidth, initSettings.screenHeight));
	}

	void ClientEngine::run() noexcept
	{
		/*
		while(!window->shouldClose())
		{
			window->display();
		}
		 */
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
