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

		Monitor getPrimaryMonitor() const noexcept final;
		std::vector<Monitor> getMonitors() const noexcept final;
	};
}

#endif //QUESTIAENGINE_GLRENDERER_H
