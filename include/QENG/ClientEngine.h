#ifndef CLIENTENGINE_H
#define CLIENTENGINE_H

#include <memory>
#include <QENG/graphics/GraphicsAPI.h>

//#include "graphics/WindowImpl.h"

namespace qe
{
	struct EngineSettings
	{
		unsigned int frameRate = 128;
		unsigned int tickRate = 60;
		unsigned int screenWidth = 1280;
		unsigned int screenHeight = 720;
	};

	class ClientEngine
	{
	public:
		explicit ClientEngine(EngineSettings initSettings = {}) noexcept;

		void run() noexcept;

		void setTickRate(unsigned int tickRate) noexcept;
		unsigned int getTickRate() const noexcept;
		void setFrameRate(unsigned int frameRate) noexcept;
		unsigned int getFrameRate() const noexcept;

	private:
		std::unique_ptr<GraphicsAPIBase> renderer;
	//	std::unique_ptr<WindowImpl> window;
		unsigned int frameRate;
		unsigned int tickRate;
		unsigned long tickCount;
	};

}

#endif // CLIENTENGINE_H