#include "QENG/graphics/opengl/GLMonitor.h"

namespace qe
{
	static std::unordered_map<GLFWmonitor*, bool> monitorsValid = {};
	static int monitorRefCount = 0;

	GLMonitor::GLMonitor(GLFWmonitor* pMonitor) noexcept : MonitorBase(), pMonitor(pMonitor)
	{
		if (monitorRefCount == 0)
		{
			glfwSetMonitorCallback(GLMonitor::monitorCallback);
			int count;
			GLFWmonitor** pMonitors = glfwGetMonitors(&count);
			for (unsigned int i = 0; i < static_cast<unsigned int>(count); i++)
			{
				monitorsValid[pMonitors[i]] = true;
			}
		}
		monitorRefCount++;
	}

	GLMonitor::~GLMonitor() noexcept
	{
		monitorRefCount--;
		if(monitorRefCount == 0)
		{
			monitorsValid.clear();
		}
	}

	std::string GLMonitor::getMonitorName() const noexcept
	{
		return glfwGetMonitorName(pMonitor);
	}

	bool GLMonitor::isConnected() const noexcept
	{
		return monitorsValid.count(pMonitor) ? monitorsValid.at(pMonitor) : false;
	}

	void GLMonitor::monitorCallback(GLFWmonitor* pMonitor, int event)
	{
		if (event == GLFW_CONNECTED)
		{
			monitorsValid[pMonitor] = true;
		}
		else if (event == GLFW_DISCONNECTED)
		{
			monitorsValid[pMonitor] = false;
		}

		// TODO create new event
	}
}
