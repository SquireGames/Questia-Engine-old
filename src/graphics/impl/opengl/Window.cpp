#include <QENG/graphics/Window.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "QENG/graphics/impl/opengl/Window.h"

namespace qe::gl
{
	Window::Window(GraphicsAPIBase* pAPI, const std::string& title, const WindowOptions& options, const qe::Monitor& monitor, Window* pSharedContext) noexcept :
			WindowBase(pAPI)
			, pMonitor (static_cast<GLFWmonitor*>(pAPI->getBase(&monitor)->getMonitorHandle()))
			, pWindow(nullptr)
			, width(options.videoMode.width)
			, height(options.videoMode.height)
			, mode(options.initMode)
	{
		glfwWindowHint(GLFW_REFRESH_RATE, options.videoMode.refreshRate ? options.videoMode.refreshRate : GLFW_DONT_CARE);
		glfwWindowHint(GLFW_RED_BITS, options.videoMode.redBits ? options.videoMode.redBits : GLFW_DONT_CARE);
		glfwWindowHint(GLFW_GREEN_BITS, options.videoMode.greenBits ? options.videoMode.greenBits : GLFW_DONT_CARE);
		glfwWindowHint(GLFW_BLUE_BITS, options.videoMode.blueBits ? options.videoMode.blueBits : GLFW_DONT_CARE);

		GLFWwindow* pSharedContextWindow = pSharedContext ? dynamic_cast<Window*>(pAPI->getBase(pSharedContext))->pWindow : nullptr;
		pWindow = glfwCreateWindow(width, height, title.c_str()
				, options.initMode == WindowMode::fullscreen ? pMonitor : nullptr, pSharedContextWindow);

		glfwSetWindowAttrib(pWindow, GLFW_RESIZABLE, options.windowedOptions.resizable);
		// TODO set the rest of the options

		if(!pWindow)
		{
			std::cout << "Error creating window" << std::endl;
			glfwTerminate();
			std::terminate();
		}
		glfwSetWindowUserPointer(pWindow, this);
		glfwSetWindowSizeCallback(pWindow, [](GLFWwindow* window, int width, int height)
		{
			auto* pThis = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
			pThis->width = static_cast<unsigned int>(width);
			pThis->height = static_cast<unsigned int>(height);
		});

		glfwMakeContextCurrent(pWindow);
		initGladLoader();
	}

	Window::~Window() noexcept
	{
		glfwDestroyWindow(pWindow);
	}

	void qe::GLWindow::display() noexcept
	{
		glfwSwapBuffers(pWindow);
	}

	void Window::toFullScreen() noexcept
	{
		if(mode != WindowMode::fullscreen)
		{
			mode = WindowMode::fullscreen;
			const GLFWvidmode* vidMode = glfwGetVideoMode(pMonitor);
			width = static_cast<unsigned int>(vidMode->width);
			height = static_cast<unsigned int>(vidMode->height);
			glfwSetWindowMonitor(pWindow, pMonitor, 0, 0, vidMode->width, vidMode->height, vidMode->refreshRate);
		}
	}

	void Window::toWindowed(unsigned int width, unsigned int height) noexcept
	{
		if(mode != WindowMode::windowed)
		{
			mode = WindowMode::windowed;
			this->width = width;
			this->height = height;
			glfwSetWindowMonitor(pWindow, nullptr, 20, 50, width, height, GLFW_DONT_CARE);
		}
	}

	void Window::resize(unsigned int width, unsigned int height) noexcept
	{
		if(mode == WindowMode::windowed)
		{
			glfwSetWindowSize(pWindow, width, height);
		}
	}

	void Window::setTitle(const std::string& title) noexcept
	{
		glfwSetWindowTitle(this->pWindow, title.c_str());
	}

	unsigned int Window::getWidth() const noexcept
	{
		return width;
	}

	unsigned int Window::getHeight() const noexcept
	{
		return height;
	}

	WindowMode Window::getMode() const noexcept
	{
		return mode;
	}

	bool Window::shouldClose() const noexcept
	{
		return static_cast<bool>(glfwWindowShouldClose(pWindow));
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

	void Window::resetShouldClose() noexcept
	{
		glfwSetWindowShouldClose(pWindow, GLFW_FALSE);
	}
}



