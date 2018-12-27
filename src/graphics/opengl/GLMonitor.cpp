#include "QENG/graphics/opengl/GLMonitor.h"

namespace qe
{
	GLMonitor::GLMonitor(GLFWmonitor* pMonitor) noexcept : MonitorBase(), pMonitor(pMonitor)
	{
	}

	std::string GLMonitor::getMonitorName()
	{
		return glfwGetMonitorName(const_cast<GLFWmonitor*>(pMonitor));
	}
}
