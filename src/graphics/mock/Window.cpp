#include "QENG/graphics/Window.h"
#include <iostream>

namespace qe
{
	class Window::Impl
	{
	public:
		explicit Impl(const std::string& title, unsigned int width, unsigned int height) noexcept;
		std::string title;
		unsigned int width;
		unsigned int height;
		Mode mode;
	};

	Window::Impl::Impl(const std::string& title, unsigned int width, unsigned int height) noexcept :
			title(title),
			width(width),
			height(height),
			mode(mode)
	{
	}

	Window::Window(const std::string& title, unsigned int width, unsigned int height) noexcept:
			pImpl(title, width, height)
	{}

	Window::~Window() noexcept
	{}

	void Window::update() noexcept
	{}

	void Window::toFullscreen() noexcept
	{}

	void Window::toWindowed(unsigned int width, unsigned int height) noexcept
	{}

	Window::Mode Window::getMode() const noexcept
	{
		return pImpl->mode;
	}

	bool Window::isClosed() const noexcept
	{
		return false;
	}

	void* Window::getUnderlyingWindow() const noexcept
	{
		return nullptr;
	}

	unsigned int Window::getWidth() const noexcept
	{
		return pImpl->width;
	}

	unsigned int Window::getHeight() const noexcept
	{
		return pImpl->height;
	}

	void Window::resize(unsigned int width, unsigned int height) noexcept
	{}

	void Window::setTitle(const std::string& title) noexcept
	{
		pImpl->title = title;
	}

}
