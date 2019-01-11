#include "QENG/graphics/opengl/GLMonitor.h"
#include <mutex>

namespace qe
{
	static std::unordered_map<GLFWmonitor*, bool> monitorsValid = {};
	static std::mutex monitorLock;
	static int monitorRefCount = 0;

	GLMonitor::GLMonitor(GLFWmonitor* pMonitor) noexcept : MonitorBase(), pMonitor(pMonitor), monitorName(std::string(glfwGetMonitorName(pMonitor)))
	{
		std::lock_guard<std::mutex> lock(monitorLock);

		// if this is the first initialized GLMonitor object
		if(monitorRefCount == 0)
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
		std::lock_guard<std::mutex> lock(monitorLock);

		monitorRefCount--;
		if(monitorRefCount == 0)
		{
			monitorsValid.clear();
		}
	}

	std::string GLMonitor::getMonitorName() const noexcept
	{
		return monitorName;
	}

	bool GLMonitor::isConnected() const noexcept
	{
		std::lock_guard<std::mutex> lock(monitorLock);
		return monitorsValid.count(pMonitor) ? monitorsValid.at(pMonitor) : false;
	}

	void GLMonitor::monitorCallback(GLFWmonitor* pMonitor, int event)
	{
		std::lock_guard<std::mutex> lock(monitorLock);
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
