#include <QENG/Window.h>
#include <iostream>

namespace qe
{
	Window::Window(const std::string& title, unsigned int width, unsigned int height) noexcept :
			width(width)
			, height(height)
			, mode(Mode::windowed)
	{
		initWindow(title, width, height, nullptr);
		glfwMakeContextCurrent(window);
		initGladLoader();
	}

	Window::Window(const std::string& title, GLFWmonitor* monitor) noexcept :
			mode(Mode::fullscreen)
	{
		const GLFWvidmode* vidMode = applyWindowHint(monitor);
		width = static_cast<unsigned int>(vidMode->width);
		height = static_cast<unsigned int>(vidMode->height);
		initWindow(title, width, height, monitor);
		glfwMakeContextCurrent(window);
		initGladLoader();
	}

	Window::~Window() noexcept
	{
		glfwDestroyWindow(window);
	}

	void Window::update() noexcept
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void Window::toFullscreen(GLFWmonitor* monitor) noexcept
	{
		if(mode != Mode::fullscreen)
		{
			mode = Mode::fullscreen;
			const GLFWvidmode* vidMode = glfwGetVideoMode(monitor);
			width = static_cast<unsigned int>(vidMode->width);
			height = static_cast<unsigned int>(vidMode->height);
			glfwSetWindowMonitor(window, monitor, 0, 0, vidMode->width, vidMode->height, vidMode->refreshRate);
		}
	}

	void Window::toWindowed(unsigned int width, unsigned int height) noexcept
	{
		if(mode != Mode::windowed)
		{
			mode = Mode::windowed;
			this->width = width;
			this->height = height;
			glfwSetWindowMonitor(window, nullptr, 20, 50, width, height, GLFW_DONT_CARE);
		}
	}

	Window::Mode Window::getMode() const noexcept
	{
		return mode;
	}

	bool Window::isClosed() const noexcept
	{
		return static_cast<bool>(glfwWindowShouldClose(window));
	}

	void* Window::getUnderlyingWindow() const noexcept
	{
		return window;
	}

	void Window::initWindow(const std::string& title, unsigned int width, unsigned int height, GLFWmonitor* monitor)
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
			auto* pThis = static_cast<Window*>(glfwGetWindowUserPointer(window));
			pThis->width = static_cast<unsigned int>(width);
			pThis->height = static_cast<unsigned int>(height);
		});
	}

	void Window::initGladLoader() const noexcept
	{
		if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			std::cout << "Error initializing glad" << std::endl;
			glfwTerminate();
			std::terminate();
		}
	}

	const GLFWvidmode* Window::applyWindowHint(GLFWmonitor* monitor)
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
		return width;
	}

	unsigned int Window::getHeight() const noexcept
	{
		return height;
	}

	void Window::resize(unsigned int width, unsigned int height) noexcept
	{
		if(mode == Mode::windowed)
		{
			glfwSetWindowSize(window, width, height);
		}
	}

	void Window::setTitle(const std::string& title) noexcept
	{
		glfwSetWindowTitle(window, title.c_str());
	}

}
