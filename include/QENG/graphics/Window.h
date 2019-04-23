#ifndef QUESTIAENGINE_WINDOW_H
#define QUESTIAENGINE_WINDOW_H

#include <string>
#include <memory>

#include "QENG/graphics/Monitor.h"
#include "QENG/graphics/WindowOptions.h"

namespace qe
{
	class WindowBase;

	class Window
	{
	public:
		enum class Mode { windowed, fullscreen };

		explicit Window(const std::string& title, const WindowOptions& options, const qe::Monitor& monitor) noexcept;
		Window(const Window&) = delete;
		Window(Window&&) noexcept = default;
		Window& operator=(Window) noexcept = delete;
		Window& operator=(Window&&) noexcept = default;
		~Window() noexcept = default;

		void update() noexcept;
		void toFullscreen() noexcept;
		void toWindowed(unsigned int width, unsigned int height) noexcept;
		void resize(unsigned int width, unsigned int height) noexcept;
		void setTitle(const std::string& title) noexcept;
		unsigned int getWidth() const noexcept;
		unsigned int getHeight() const noexcept;
		Mode getMode() const noexcept;
		void* getUnderlyingWindow() const noexcept;

		bool isClosed() const noexcept;

	private:
		std::unique_ptr<WindowBase> windowBase;
	};


	class WindowBase
	{
	public:
		virtual ~WindowBase() noexcept = default;
		virtual void update() noexcept = 0;
		virtual void toFullScreen() noexcept = 0;

		virtual void toWindowed(unsigned int width, unsigned int height) noexcept = 0;
		virtual void resize(unsigned int width, unsigned int height) noexcept = 0;
		virtual void setTitle(const std::string& title) noexcept = 0;

		virtual unsigned int getWidth() const noexcept = 0;
		virtual unsigned int getHeight() const noexcept = 0;
		virtual Window::Mode getMode() const noexcept = 0;
		virtual void* getUnderlyingWindow() const noexcept = 0;

		virtual bool isClosed() const noexcept = 0;
	protected:
		explicit WindowBase() noexcept = default;
	};


	inline qe::Window::Window(const std::string& title, const WindowOptions& options,
							  const qe::Monitor& monitor) noexcept
			: windowBase(monitor.getWindowConstructor()(title, options, monitor))
	{
	}

	inline void Window::update() noexcept
	{
		windowBase->update();
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

	inline Window::Mode Window::getMode() const noexcept
	{
		return windowBase->getMode();
	}

	inline void* Window::getUnderlyingWindow() const noexcept
	{
		return windowBase->getUnderlyingWindow();
	}

	inline bool Window::isClosed() const noexcept
	{
		return windowBase->isClosed();
	}
}

#endif //QUESTIAENGINE_WINDOW_H
