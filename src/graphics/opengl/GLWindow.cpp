#include <QENG/graphics/Window.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "QENG/graphics/opengl/GLWindow.h"

namespace qe
{
	GLWindow::GLWindow(const std::string& title, const WindowOptions& options, const qe::Monitor& monitor, const Window* pSharedContext) noexcept :
			pMonitor (static_cast<GLFWmonitor*>(monitor.getMonitorPtr()->getMonitorHandle()))
			, pWindow(nullptr)
			, width(options.videoMode.width)
			, height(options.videoMode.height)
			, mode(options.initMode)
	{
		glfwWindowHint(GLFW_REFRESH_RATE, options.videoMode.refreshRate ? options.videoMode.refreshRate : GLFW_DONT_CARE);
		glfwWindowHint(GLFW_RED_BITS, options.videoMode.redBits ? options.videoMode.redBits : GLFW_DONT_CARE);
		glfwWindowHint(GLFW_GREEN_BITS, options.videoMode.greenBits ? options.videoMode.greenBits : GLFW_DONT_CARE);
		glfwWindowHint(GLFW_BLUE_BITS, options.videoMode.blueBits ? options.videoMode.blueBits : GLFW_DONT_CARE);


		GLFWwindow* pSharedContextWindow = pSharedContext ? dynamic_cast<GLWindow*>(pSharedContext->getWindowPtr())->pWindow : nullptr;
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
			auto* pThis = reinterpret_cast<GLWindow*>(glfwGetWindowUserPointer(window));
			pThis->width = static_cast<unsigned int>(width);
			pThis->height = static_cast<unsigned int>(height);
		});

		glfwMakeContextCurrent(pWindow);
		initGladLoader();
	}

	GLWindow::~GLWindow() noexcept
	{
		glfwDestroyWindow(pWindow);
	}

	void qe::GLWindow::display() noexcept
	{
		glfwSwapBuffers(pWindow);
	}

	void GLWindow::toFullScreen() noexcept
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

	void GLWindow::toWindowed(unsigned int width, unsigned int height) noexcept
	{
		if(mode != WindowMode::windowed)
		{
			mode = WindowMode::windowed;
			this->width = width;
			this->height = height;
			glfwSetWindowMonitor(pWindow, nullptr, 20, 50, width, height, GLFW_DONT_CARE);
		}
	}

	void GLWindow::resize(unsigned int width, unsigned int height) noexcept
	{
		if(mode == WindowMode::windowed)
		{
			glfwSetWindowSize(pWindow, width, height);
		}
	}

	void GLWindow::setTitle(const std::string& title) noexcept
	{
		glfwSetWindowTitle(this->pWindow, title.c_str());
	}

	unsigned int GLWindow::getWidth() const noexcept
	{
		return width;
	}

	unsigned int GLWindow::getHeight() const noexcept
	{
		return height;
	}

	WindowMode GLWindow::getMode() const noexcept
	{
		return mode;
	}

	bool GLWindow::shouldClose() const noexcept
	{
		return static_cast<bool>(glfwWindowShouldClose(pWindow));
	}


	void GLWindow::initGladLoader() const noexcept
	{
		if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			std::cout << "Error initializing glad" << std::endl;
			glfwTerminate();
			std::terminate();
		}
	}

	void GLWindow::resetShouldClose() noexcept
	{
		glfwSetWindowShouldClose(pWindow, GLFW_FALSE);
	}
}



