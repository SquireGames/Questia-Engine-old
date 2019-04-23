#include <QENG/graphics/Window.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <QENG/graphics/opengl/GLWindow.h>


namespace qe
{
	void qe::GLWindow::update() noexcept
	{

	}

	void GLWindow::toFullScreen() noexcept
	{

	}

	void GLWindow::toWindowed(unsigned int width, unsigned int height) noexcept
	{

	}

	void GLWindow::resize(unsigned int width, unsigned int height) noexcept
	{

	}

	void GLWindow::setTitle(const std::string& title) noexcept
	{

	}

	unsigned int GLWindow::getWidth() const noexcept
	{
		return 100;
	}

	unsigned int GLWindow::getHeight() const noexcept
	{
		return 0;
	}

	Window::Mode GLWindow::getMode() const noexcept
	{
		return qe::Window::Mode::fullscreen;
	}

	void* GLWindow::getUnderlyingWindow() const noexcept
	{
		return nullptr;
	}

	bool GLWindow::isClosed() const noexcept
	{
		return false;
	}

	GLWindow::~GLWindow() noexcept
	{
	}

	GLWindow::GLWindow(const std::string& title, const WindowOptions& options, const qe::Monitor& monitor) noexcept
	{
	}
}



/*

namespace qe
{
	class Window::Impl
	{
	public:
		Impl(const std::string& title, unsigned int width, unsigned int height);

		void initWindow(const std::string& title, unsigned int width, unsigned int height, GLFWmonitor* monitor);
		void initGladLoader() const noexcept;
		const GLFWvidmode* applyWindowHint(GLFWmonitor* monitor);

		GLFWmonitor* monitor;
		GLFWwindow* window;
		unsigned int width;
		unsigned int height;
		Mode mode;
	};

	Window::Impl::Impl(const std::string& title, unsigned int width, unsigned int height) :
			monitor(glfwGetPrimaryMonitor()),
			window(nullptr),
			width(width),
			height(height),
			mode(Mode::fullscreen)
	{
		const GLFWvidmode* vidMode = applyWindowHint(monitor);
		width = static_cast<unsigned int>(vidMode->width);
		height = static_cast<unsigned int>(vidMode->height);
		initWindow(title, width, height, nullptr);
		glfwMakeContextCurrent(window);
		initGladLoader();
	}

	Window::Window(const std::string& title, unsigned int width, unsigned int height) noexcept :
			pImpl(title, width, height)
	{
	}

	Window::~Window() noexcept
	{
		glfwDestroyWindow(pImpl->window);
	}

	void Window::update() noexcept
	{
		glfwPollEvents();
		glfwSwapBuffers(pImpl->window);
	}

	void Window::toFullscreen() noexcept
	{
		if(pImpl->mode != Mode::fullscreen)
		{
			pImpl->mode = Mode::fullscreen;
			const GLFWvidmode* vidMode = glfwGetVideoMode(pImpl->monitor);
			pImpl->width = static_cast<unsigned int>(vidMode->width);
			pImpl->height = static_cast<unsigned int>(vidMode->height);
			glfwSetWindowMonitor(pImpl->window, pImpl->monitor, 0, 0, vidMode->width, vidMode->height, vidMode->refreshRate);
		}
	}

	void Window::toWindowed(unsigned int width, unsigned int height) noexcept
	{
		if(pImpl->mode != Mode::windowed)
		{
			pImpl->mode = Mode::windowed;
			pImpl->width = width;
			pImpl->height = height;
			glfwSetWindowMonitor(pImpl->window, nullptr, 20, 50, width, height, GLFW_DONT_CARE);
		}
	}

	Window::Mode Window::getMode() const noexcept
	{
		return pImpl->mode;
	}

	bool Window::isClosed() const noexcept
	{
		return static_cast<bool>(glfwWindowShouldClose(pImpl->window));
	}

	void* Window::getUnderlyingWindow() const noexcept
	{
		return pImpl->window;
	}

	void Window::Impl::initWindow(const std::string& title, unsigned int width, unsigned int height, GLFWmonitor* monitor)
	{
		window = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
		if(!window)
		{
			std::cout << "Error creating window" << std::endl;
			glfwTerminate();
			std::terminate();
		}
		glfwSetWindowUserPointer(window, this);
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			auto* pThis = static_cast<Impl*>(glfwGetWindowUserPointer(window));
			pThis->width = static_cast<unsigned int>(width);
			pThis->height = static_cast<unsigned int>(height);
		});
	}

	void Window::Impl::initGladLoader() const noexcept
	{
		if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			std::cout << "Error initializing glad" << std::endl;
			glfwTerminate();
			std::terminate();
		}
	}

	const GLFWvidmode* Window::Impl::applyWindowHint(GLFWmonitor* monitor)
	{
		const GLFWvidmode* vidMode = glfwGetVideoMode(monitor);
		if(!vidMode)
		{
			std::cout << "Error retrieving video mode" << std::endl;
			glfwTerminate();
			std::terminate();
		}
		glfwWindowHint(GLFW_RED_BITS, vidMode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, vidMode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, vidMode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, vidMode->refreshRate);
		return vidMode;
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
	{
		if(pImpl->mode == Mode::windowed)
		{
			glfwSetWindowSize(pImpl->window, width, height);
		}
	}

	void Window::setTitle(const std::string& title) noexcept
	{
		glfwSetWindowTitle(pImpl->window, title.c_str());
	}

}

 */
