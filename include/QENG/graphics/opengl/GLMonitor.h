#ifndef QUESTIAENGINE_GLWINDOW_H
#define QUESTIAENGINE_GLWINDOW_H

#include "QENG/graphics/Monitor.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace qe
{
	class GLMonitor : public MonitorBase
	{
	public:
		std::string getMonitorName();
	private:
		friend class GLInstance;

		explicit GLMonitor(GLFWmonitor* pMonitor) noexcept;

		const GLFWmonitor* pMonitor;
	};

}

#endif //QUESTIAENGINE_GLWINDOW_H
