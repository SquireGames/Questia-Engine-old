#include "QENG/graphics/opengl/GLMonitor.h"

namespace qe
{
	GLMonitor::GLMonitor(GLFWmonitor* pMonitor) noexcept : Monitor(), pMonitor(pMonitor)
	{
	}
}
