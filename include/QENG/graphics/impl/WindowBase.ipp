
namespace qe
{
	class WindowBase
	{
	public:
		virtual ~WindowBase() noexcept = default;
		virtual void display() noexcept = 0;
		virtual void toFullScreen() noexcept = 0;

		virtual void toWindowed(unsigned int width, unsigned int height) noexcept = 0;
		virtual void resize(unsigned int width, unsigned int height) noexcept = 0;
		virtual void setTitle(const std::string& title) noexcept = 0;

		virtual unsigned int getWidth() const noexcept = 0;
		virtual unsigned int getHeight() const noexcept = 0;
		virtual WindowMode getMode() const noexcept = 0;

		virtual bool shouldClose() const noexcept = 0;
		virtual void resetShouldClose() noexcept = 0;

	protected:
		explicit WindowBase(GraphicsAPIBase* pAPI) noexcept;
		GraphicsAPIBase* const pAPI;
	};

	inline WindowBase::WindowBase(GraphicsAPIBase* pAPI) noexcept : pAPI(pAPI)
	{
	}

	inline qe::Window::Window(const std::string& title, const WindowOptions& options,
			const qe::Monitor& monitor, std::optional<Window*> sharedContext) noexcept :
			windowBase(monitor.monitorBase->pAPI->newWindowBase(title, options, monitor, sharedContext ? sharedContext.value() : nullptr))
	{
	}

	inline void Window::create(const std::string &title, const WindowOptions &options, const qe::Monitor &monitor,
			std::optional<Window*> sharedContext) noexcept
	{
		if(isClosed())
		{
			windowBase = std::unique_ptr<WindowBase>(monitor.monitorBase->pAPI->newWindowBase(title, options, monitor, sharedContext ? sharedContext.value() : nullptr));
		}
	}

	inline void Window::close() noexcept
	{
		if(!isClosed())
		{
			windowBase.reset();
		}
	}

	inline void Window::display() noexcept
	{
		windowBase->display();
	}

	inline void Window::toFullscreen() noexcept
	{
		windowBase->toFullScreen();
	}

	inline void Window::toWindowed(unsigned int width, unsigned int height) noexcept
	{
		windowBase->toWindowed(width, height);
	}

	inline void Window::resize(unsigned int width, unsigned int height) noexcept
	{
		windowBase->resize(width, height);
	}

	inline void Window::resize(Vector2ui size) noexcept
	{
		resize(size.x(), size.y());
	}

	inline void Window::setTitle(const std::string& title) noexcept
	{
		windowBase->setTitle(title);
	}

	inline unsigned int Window::getWidth() const noexcept
	{
		return windowBase->getWidth();
	}

	inline unsigned int Window::getHeight() const noexcept
	{
		return windowBase->getHeight();
	}

	inline WindowMode Window::getMode() const noexcept
	{
		return windowBase->getMode();
	}

	inline bool Window::shouldClose() const noexcept
	{
		return windowBase->shouldClose();
	}

	inline void Window::resetShouldClose() noexcept
	{
		return windowBase->resetShouldClose();
	}

	inline bool Window::isClosed() noexcept
	{
		return !static_cast<bool>(windowBase);
	}

	inline Vector2ui Window::getSize() const noexcept
	{
		return qe::Vector2ui(getWidth(), getHeight());
	}
}
