#ifndef QUESTIAENGINE_GLWINDOW_H
#define QUESTIAENGINE_GLWINDOW_H

#include "QENG/graphics/Window.h"

namespace qe
{
	class GLWindow : public WindowBase
	{
	public:
		~GLWindow() noexcept final;

		void update() noexcept final;

		void toFullScreen() noexcept final;
		void toWindowed(unsigned int width, unsigned int height) noexcept final;
		void resize(unsigned int width, unsigned int height) noexcept final;

		void setTitle(const std::string& title) noexcept final;

		unsigned int getWidth() const noexcept final;
		unsigned int getHeight() const noexcept final;
		WindowMode getMode() const noexcept final;

		bool shouldClose() const noexcept final;

	private:
		friend class GLInstance;
		friend class GLMonitor;

		void initGladLoader() const noexcept;

		GLFWmonitor* pMonitor;
		GLFWwindow* pWindow;
		unsigned int width;
		unsigned int height;
		WindowMode mode;

		// must be initialized from glfw thread
		explicit GLWindow(const std::string& title, const WindowOptions& options, const qe::Monitor& monitor, const Window* pSharedContext) noexcept;
	};
}


#endif //QUESTIAENGINE_GLWINDOW_H
