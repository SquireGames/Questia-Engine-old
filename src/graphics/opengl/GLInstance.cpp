#include "QENG/graphics/opengl/GLInstance.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <QENG/graphics/opengl/GLWindow.h>
#include "QENG/graphics/opengl/GLMonitor.h"

namespace qe
{
	GLInstance::GLInstance() noexcept : GraphicsAPIBase()
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

	GLInstance::~GLInstance()
	{
		glfwTerminate();
	}

	std::vector<Monitor> GLInstance::getMonitors() noexcept
	{
		int count;
		GLFWmonitor** pMonitors = glfwGetMonitors(&count);

		std::vector<Monitor> monitors;
		monitors.reserve(static_cast<unsigned int>(count));

		for (unsigned int i = 0; i < static_cast<unsigned int>(count); i++)
		{
			monitors.emplace_back(Monitor(std::unique_ptr<MonitorBase>(new GLMonitor(this, pMonitors[i]))));
		}

		return monitors;
	}

	Monitor GLInstance::getPrimaryMonitor() noexcept
	{
		GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
		return Monitor(std::unique_ptr<GLMonitor>(new GLMonitor(this, pMonitor)));
	}

	WindowBase* GLInstance::newWindowBase(const std::string& name, const WindowOptions& options, const Monitor& monitor, Window* pSharedContext) noexcept
	{
		return new GLWindow(this, name, options, monitor, pSharedContext);
	}

}

