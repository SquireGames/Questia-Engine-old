#include <iostream>
#include "QENG/ClientEngine.h"

namespace qe
{
	qe::ClientEngine::ClientEngine(qe::EngineSettings initSettings) noexcept :
			window()
			, frameRate(initSettings.frameRate)
			, tickRate(initSettings.tickRate)
			, tickCount(0)
	{
		if(!glfwInit())
		{
			std::cout << "Error initializing glfw" << std::endl;
			std::terminate();
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = std::unique_ptr<Window>(new Window(u8"Questia Engine game title", initSettings.screenWidth, initSettings.screenHeight));
	}

	void ClientEngine::run() noexcept
	{
		while(!window->isClosed())
		{
			window->update();
		}
		glfwTerminate();
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
