
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

	inline void GraphicsAPI::pollEvents() noexcept
	{
		graphicsAPIBase->pollEvents();
	}
}
