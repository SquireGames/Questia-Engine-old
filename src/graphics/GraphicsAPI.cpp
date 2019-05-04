#include "QENG/graphics/GraphicsAPI.h"
#include "QENG/graphics/Window.h"
#include "QENG/graphics/Monitor.h"

namespace qe
{
	WindowBase* GraphicsAPIBase::getBase(const Window* pWindow) noexcept
	{
		return pWindow->windowBase.get();
	}

	MonitorBase* GraphicsAPIBase::getBase(const Monitor* pMonitor) noexcept
	{
		return pMonitor->monitorBase.get();
	}
}
