#ifndef QUESTIAENGINE_WINDOW_H
#define QUESTIAENGINE_WINDOW_H

#include <string>
#include <memory>
#include <optional>

#include "QENG/graphics/Monitor.h"
#include "QENG/graphics/WindowOptions.h"
#include "QENG/graphics/GraphicsAPI.h"

namespace qe
{
	class WindowBase;

	class Window
	{
	public:
		explicit Window(const std::string& title, const WindowOptions& options, const qe::Monitor& monitor, std::optional<Window*> sharedContext = {}) noexcept;
		constexpr Window() noexcept = default;
		Window(const Window&) = delete;
		Window(Window&&) noexcept = default;
		Window& operator=(Window) noexcept = delete;
		Window& operator=(Window&&) noexcept = default;
		~Window() noexcept = default;

		void create(const std::string& title, const WindowOptions& options, const qe::Monitor& monitor, std::optional<Window*> sharedContext = {}) noexcept;
		void close() noexcept;

		bool shouldClose() const noexcept;
		bool isClosed() noexcept;
		void resetShouldClose() noexcept;

		void display() noexcept;
		void toFullscreen() noexcept;
		void toWindowed(unsigned int width, unsigned int height) noexcept;

		void setTitle(const std::string& title) noexcept;
		void resize(unsigned int width, unsigned int height) noexcept;
		void resize(Vector2ui size) noexcept;
		Vector2ui getSize() const noexcept;
		unsigned int getWidth() const noexcept;
		unsigned int getHeight() const noexcept;
		WindowMode getMode() const noexcept;

	private:
		std::unique_ptr<WindowBase> windowBase;

		friend GraphicsAPIBase;
	};

}

#include "QENG/graphics/impl/WindowBase.h"

namespace qe
{

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


#endif //QUESTIAENGINE_WINDOW_H
