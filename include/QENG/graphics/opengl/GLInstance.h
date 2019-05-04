#ifndef QUESTIAENGINE_GLRENDERER_H
#define QUESTIAENGINE_GLRENDERER_H

#include "QENG/graphics/GraphicsAPI.h"

namespace qe
{
	class GLInstance : public GraphicsAPIBase
	{
	public:
		explicit GLInstance() noexcept;
		~GLInstance() noexcept final;

		Monitor getPrimaryMonitor() noexcept final;
		std::vector<Monitor> getMonitors() noexcept final;

		WindowBase* newWindowBase(const std::string& name, const WindowOptions& options, const Monitor& monitor, Window* pSharedContext) noexcept final;
	};
}

#endif //QUESTIAENGINE_GLRENDERER_H
