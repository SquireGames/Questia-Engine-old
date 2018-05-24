#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace qe
{
	class Window
	{
	public:
		enum class Mode { windowed, fullscreen };

		explicit Window(const std::string& title, unsigned int width, unsigned int height) noexcept;
		explicit Window(const std::string& title, GLFWmonitor* monitor = glfwGetPrimaryMonitor()) noexcept;
		Window(const Window&) = delete;
		Window(Window&&) = default;
		Window& operator=(Window) = delete;
		Window& operator=(Window&&) = default;
		~Window() noexcept;

		void update() noexcept;
		void toFullscreen(GLFWmonitor* monitor = glfwGetPrimaryMonitor()) noexcept;
		void toWindowed(unsigned int width, unsigned int height) noexcept;
		void resize(unsigned int width, unsigned int height) noexcept;
		void setTitle(const std::string& title) noexcept;

		unsigned int getWidth() const noexcept;
		unsigned int getHeight() const noexcept;
		Mode getMode() const noexcept;
		void* getUnderlyingWindow() const noexcept;

		bool isClosed() const noexcept;

	private:
		void initWindow(const std::string& title, unsigned int width, unsigned int height, GLFWmonitor* monitor);
		void initGladLoader() const noexcept;
		const GLFWvidmode* applyWindowHint(GLFWmonitor* monitor);

		GLFWwindow* window;
		unsigned int width;
		unsigned int height;
		Mode mode;
	};
}

#endif //WINDOW_H
