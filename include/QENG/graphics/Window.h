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

#include "QENG/graphics/impl/WindowBase.ipp"

#endif //QUESTIAENGINE_WINDOW_H
