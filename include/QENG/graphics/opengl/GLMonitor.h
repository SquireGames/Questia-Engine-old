#ifndef QUESTIAENGINE_GLWINDOW_H
#define QUESTIAENGINE_GLWINDOW_H

#include "QENG/graphics/Monitor.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace qe
{
	class GLMonitor : public Monitor
	{
	public:

	private:
		friend class GLInstance;

		explicit GLMonitor(GLFWmonitor* pMonitor) noexcept;

		const GLFWmonitor* pMonitor;
	};

}

#endif //QUESTIAENGINE_GLWINDOW_H
