#ifndef QUESTIAENGINE_GRAPHICSAPI_H
#define QUESTIAENGINE_GRAPHICSAPI_H

#include <vector>
#include <memory>
#include "QENG/graphics/Monitor.h"

namespace qe
{
	class GraphicsAPIBase;

	class GraphicsAPI
	{
	public:
		explicit GraphicsAPI(std::unique_ptr<GraphicsAPIBase> graphicsAPIBase) noexcept;
		~GraphicsAPI() noexcept = default;

		Monitor getPrimaryMonitor() const noexcept;
		std::vector<Monitor> getMonitors() const noexcept;

		void pollEvents() noexcept;

		// requires that all classes that depend on this class be deconstructed
		void changeAPI(std::unique_ptr<GraphicsAPIBase> newAPI) noexcept;

	private:
		std::unique_ptr<GraphicsAPIBase> graphicsAPIBase;
	};
}

#include "QENG/Graphics/impl/GraphicsAPIBase.ipp"

#endif //QUESTIAENGINE_GRAPHICSAPI_H
