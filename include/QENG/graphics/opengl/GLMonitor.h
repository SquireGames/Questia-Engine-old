#ifndef QUESTIAENGINE_GLWINDOW_H
#define QUESTIAENGINE_GLWINDOW_H

#include "QENG/graphics/Monitor.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>

namespace qe
{
	class GLMonitor : public MonitorBase
	{
	public:
		~GLMonitor() noexcept final;

		std::string getMonitorName() const noexcept final;
		void setMonitorCallback(std::function<void(const Monitor&, Monitor::State)> callback) const noexcept final;

		void* getMonitorHandle() const noexcept final;

		bool operator==(MonitorBase* other) const noexcept final;

	private:
		friend class GLInstance;

		// must be initialized from glfw thread
		explicit GLMonitor(GLFWmonitor* pMonitor) noexcept;

		static void monitorCallback(GLFWmonitor* pMonitor, int event);

		GLFWmonitor* const pMonitor;
		std::string monitorName;
	};

}

#endif //QUESTIAENGINE_GLWINDOW_H
