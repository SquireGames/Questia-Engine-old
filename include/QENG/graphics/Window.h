#ifndef WINDOW_H
#define WINDOW_H

#include <string>

namespace qe
{
	class Window
	{
	public:
		enum class Mode { windowed, fullscreen };

		explicit Window(const std::string& title, unsigned int width, unsigned int height) noexcept;
		Window(const Window&) = delete;
		Window(Window&&) noexcept = default;
		Window& operator=(Window) noexcept = delete;
		Window& operator=(Window&&) noexcept = default;
		~Window() noexcept;

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

	};
}

#endif //WINDOW_H
