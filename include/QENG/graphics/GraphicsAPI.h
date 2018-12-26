#ifndef QUESTIAENGINE_RENDERER_H
#define QUESTIAENGINE_RENDERER_H

#include <vector>
#include "Monitor.h"

namespace qe
{
	class GraphicsAPI
	{
	public:
		explicit GraphicsAPI() noexcept = default;
		virtual ~GraphicsAPI() noexcept = default;

		virtual Monitor* getPrimaryMonitor() const noexcept = 0;
		virtual std::vector<Monitor*> getMonitors() const noexcept = 0;
	};
}

#endif //QUESTIAENGINE_RENDERER_H
