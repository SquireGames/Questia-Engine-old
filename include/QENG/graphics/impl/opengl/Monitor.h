#ifndef QUESTIAENGINE_GLMONITOR_H
#define QUESTIAENGINE_GLMONITOR_H

#include "QENG/graphics/Monitor.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>
#include "QENG/graphics/Window.h"

namespace qe::gl
{
	class Monitor : public MonitorBase
	{
	public:
		~Monitor() noexcept final;

		bool operator==(MonitorBase* other) const noexcept final;

		std::string getName() const noexcept final;
		Vector2i getPosition() const noexcept final;
		Vector2ui getPhysicalSize() const noexcept final;

		void setMonitorCallback(std::function<void(const qe::Monitor&, qe::Monitor::State)> callback) const noexcept final;

		VideoMode getVideoMode() const noexcept final;
		std::vector<VideoMode> getVideoModes() const noexcept final;

		qe::Monitor::GammaRamp getGammaRamp() const noexcept final;
		bool setGammaRamp(const qe::Monitor::GammaRamp& ramp) noexcept final;
		bool setGamma(float gamma) noexcept final;

		void* getMonitorHandle() const noexcept final;

		std::unique_ptr<MonitorBase> clone() const noexcept final;

	private:
		friend class GraphicsAPI;

		// must be initialized from glfw thread
		explicit Monitor(GraphicsAPIBase* pAPI, GLFWmonitor* pMonitor) noexcept;

		static void monitorCallback(GLFWmonitor* pMonitor, int event);

		GLFWmonitor* const pMonitor;
		std::string monitorName;
	};

}

#endif //QUESTIAENGINE_GLMONITOR_H
