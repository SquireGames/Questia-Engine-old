#include "QENG/graphics/opengl/GLMonitor.h"
#include <mutex>

namespace qe
{
	static std::mutex monitorLock;
	static int monitorRefCount = 0;
	static std::function<void(const Monitor&, Monitor::State)> monitorConnectionCallback = {};

	GLMonitor::GLMonitor(GLFWmonitor* pMonitor) noexcept : MonitorBase(), pMonitor(pMonitor), monitorName(std::string(glfwGetMonitorName(pMonitor)))
	{
		std::lock_guard<std::mutex> lock(monitorLock);

		// if this is the first initialized GLMonitor object
		if(monitorRefCount == 0)
		{
			glfwSetMonitorCallback(GLMonitor::monitorCallback);
		}
		monitorRefCount++;
	}

    GLMonitor::~GLMonitor() noexcept
	{
		std::lock_guard<std::mutex> lock(monitorLock);
		monitorRefCount--;
	}

	std::string GLMonitor::getMonitorName() const noexcept
	{
		return monitorName;
	}

	void GLMonitor::monitorCallback(GLFWmonitor* pMonitor, int event)
	{
		// only call the callback if the callback was set
		{
			std::lock_guard<std::mutex> lock(monitorLock);
			if (!monitorConnectionCallback) {
				return;
			}
		}
		// ctor must not be locked because the constructor locks with the same mutex
		Monitor monitor = Monitor(std::unique_ptr<MonitorBase>(new GLMonitor(pMonitor)));

		std::lock_guard<std::mutex> lock(monitorLock);
		if (event == GLFW_CONNECTED)
		{
			monitorConnectionCallback(monitor, Monitor::State::connected);
		}
		else if (event == GLFW_DISCONNECTED)
		{
			monitorConnectionCallback(monitor, Monitor::State::disconnected);
		}
	}

	void GLMonitor::setMonitorCallback(std::function<void(const Monitor&, Monitor::State)> callback) const noexcept
	{
		std::lock_guard<std::mutex> lock(monitorLock);
		qe::monitorConnectionCallback = callback;
	}

	bool GLMonitor::operator==(MonitorBase* other) const noexcept
	{
		return pMonitor == other->getMonitorHandle();
	}

	void *GLMonitor::getMonitorHandle() const noexcept
	{
		return pMonitor;
	}

}
