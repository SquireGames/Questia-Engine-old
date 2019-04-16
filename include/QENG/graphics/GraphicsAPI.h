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

	private:
		std::unique_ptr<GraphicsAPIBase> graphicsAPIBase;
	};


	class GraphicsAPIBase
	{
	public:
		explicit GraphicsAPIBase() noexcept = default;
		virtual ~GraphicsAPIBase() noexcept = default;

		virtual Monitor getPrimaryMonitor() const noexcept = 0;
		virtual std::vector<Monitor> getMonitors() const noexcept = 0;
	};

	inline GraphicsAPI::GraphicsAPI(std::unique_ptr<GraphicsAPIBase> graphicsAPIBase) noexcept : graphicsAPIBase(std::move(graphicsAPIBase))
	{
	}

	inline Monitor GraphicsAPI::getPrimaryMonitor() const noexcept
	{
		return graphicsAPIBase->getPrimaryMonitor();
	}

	inline std::vector<Monitor> GraphicsAPI::getMonitors() const noexcept
	{
		return graphicsAPIBase->getMonitors();
	}
}

#endif //QUESTIAENGINE_GRAPHICSAPI_H
