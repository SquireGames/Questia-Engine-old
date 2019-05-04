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

		// requires that all classes that depend on this class be deconstructed
		void changeAPI(std::unique_ptr<GraphicsAPIBase> newAPI) noexcept;

		Monitor getPrimaryMonitor() const noexcept;
		std::vector<Monitor> getMonitors() const noexcept;

	private:
		std::unique_ptr<GraphicsAPIBase> graphicsAPIBase;
	};


	class Window;
	class WindowBase;

	class GraphicsAPIBase
	{
	public:
		explicit GraphicsAPIBase() noexcept = default;
		virtual ~GraphicsAPIBase() noexcept = default;

		virtual Monitor getPrimaryMonitor() noexcept = 0;
		virtual std::vector<Monitor> getMonitors() noexcept = 0;

		virtual [[nodiscard]] WindowBase* newWindowBase(const std::string&, const WindowOptions&, const Monitor&, Window*) noexcept = 0;

		WindowBase* getBase(const Window* pWindow) noexcept;
		MonitorBase* getBase(const Monitor* pMonitor) noexcept;
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

	inline void GraphicsAPI::changeAPI(std::unique_ptr<GraphicsAPIBase> newAPI) noexcept
	{
		graphicsAPIBase.reset();
		graphicsAPIBase = std::move(newAPI);
	}
}

#endif //QUESTIAENGINE_GRAPHICSAPI_H
