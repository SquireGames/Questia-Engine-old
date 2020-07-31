#ifndef QUESTIAENGINE_GLRENDERER_H
#define QUESTIAENGINE_GLRENDERER_H

#include "QENG/graphics/GraphicsAPI.h"

namespace qe::gl
{
	class GraphicsAPIImpl : public GraphicsAPIBase
	{
	public:
		explicit GraphicsAPIImpl() noexcept;
		~GraphicsAPIImpl() noexcept final;

		qe::Monitor getPrimaryMonitor() noexcept final;
		std::vector<qe::Monitor> getMonitors() noexcept final;

		void pollEvents() noexcept final;

		WindowBase* newWindowBase(const std::string& name, const WindowOptions& options, const qe::Monitor& monitor, qe::Window* pSharedContext) noexcept final;
	};
}

#endif //QUESTIAENGINE_GLRENDERER_H

