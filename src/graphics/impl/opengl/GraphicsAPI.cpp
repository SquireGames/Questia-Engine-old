#include "QENG/graphics/impl/opengl/GraphicsAPI.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <QENG/graphics/impl/opengl/Window.h>
#include "QENG/graphics/impl/opengl/Monitor.h"

namespace qe::gl
{
	GraphicsAPI::GraphicsAPI() noexcept : GraphicsAPIBase()
	{
		if(!glfwInit())
		{
			std::cout << "Error initializing glfw" << std::endl;
			std::terminate();
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	GraphicsAPI::~GraphicsAPI()
	{
		glfwTerminate();
	}

	std::vector<qe::Monitor> GraphicsAPI::getMonitors() noexcept
	{
		int count;
		GLFWmonitor** pMonitors = glfwGetMonitors(&count);

		std::vector<qe::Monitor> monitors;
		monitors.reserve(static_cast<unsigned int>(count));

		for (unsigned int i = 0; i < static_cast<unsigned int>(count); i++)
		{
			monitors.emplace_back(qe::Monitor(std::unique_ptr<MonitorBase>(new Monitor(this, pMonitors[i]))));
		}

		return monitors;
	}

	qe::Monitor GraphicsAPI::getPrimaryMonitor() noexcept
	{
		GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
		return qe::Monitor(std::unique_ptr<qe::gl::Monitor>(new qe::gl::Monitor(this, pMonitor)));
	}

	WindowBase* GraphicsAPI::newWindowBase(const std::string& name, const WindowOptions& options, const qe::Monitor& monitor, qe::Window* pSharedContext) noexcept
	{
		return new Window(this, name, options, monitor, pSharedContext);
	}

	void GraphicsAPI::pollEvents() noexcept
	{
		glfwPollEvents();
	}
}

