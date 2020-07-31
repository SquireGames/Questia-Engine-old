#include "QENG/graphics/impl/opengl/GraphicsAPIImpl.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <QENG/graphics/impl/opengl/WindowImpl.h>
#include "QENG/graphics/impl/opengl/MonitorImpl.h"

namespace qe::gl
{
	GraphicsAPIImpl::GraphicsAPIImpl() noexcept : GraphicsAPIBase()
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

	GraphicsAPIImpl::~GraphicsAPIImpl()
	{
		glfwTerminate();
	}

	std::vector<qe::Monitor> GraphicsAPIImpl::getMonitors() noexcept
	{
		int count;
		GLFWmonitor** pMonitors = glfwGetMonitors(&count);

		std::vector<qe::Monitor> monitors;
		monitors.reserve(static_cast<unsigned int>(count));

		for (unsigned int i = 0; i < static_cast<unsigned int>(count); i++)
		{
			monitors.emplace_back(qe::Monitor(std::unique_ptr<MonitorBase>(new MonitorImpl(this, pMonitors[i]))));
		}

		return monitors;
	}

	qe::Monitor GraphicsAPIImpl::getPrimaryMonitor() noexcept
	{
		GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
		return qe::Monitor(std::unique_ptr<MonitorImpl>(new MonitorImpl(this, pMonitor)));
	}

	WindowBase* GraphicsAPIImpl::newWindowBase(const std::string& name, const WindowOptions& options, const qe::Monitor& monitor, qe::Window* pSharedContext) noexcept
	{
		return new WindowImpl(this, name, options, monitor, pSharedContext);
	}

	void GraphicsAPIImpl::pollEvents() noexcept
	{
		glfwPollEvents();
	}
}

