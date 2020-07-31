#ifndef QUESTIAENGINE_GRAPHICSAPIBASE_H
#define QUESTIAENGINE_GRAPHICSAPIBASE_H

namespace qe
{
	class Window;
	class WindowBase;

	class GraphicsAPIBase
	{
	public:
		explicit GraphicsAPIBase() noexcept = default;
		virtual ~GraphicsAPIBase() noexcept = default;

		virtual Monitor getPrimaryMonitor() noexcept = 0;
		virtual std::vector<Monitor> getMonitors() noexcept = 0;

		virtual void pollEvents() noexcept = 0;

		virtual [[nodiscard]] WindowBase* newWindowBase(const std::string&, const WindowOptions&, const Monitor&, Window*) noexcept = 0;

		WindowBase* getBase(const Window* pWindow) noexcept;
		MonitorBase* getBase(const Monitor* pMonitor) noexcept;
	};

}

#endif //QUESTIAENGINE_GRAPHICSAPIBASE_H