#ifndef QUESTIAENGINE_MONITOR_H
#define QUESTIAENGINE_MONITOR_H

#include <memory>
#include <string>
#include <functional>
#include <vector>

#include "QENG/math/FixedVector.h"
#include "QENG/graphics/VideoMode.h"
#include "QENG/graphics/WindowOptions.h"

namespace qe
{
	class MonitorBase;
	class Window;
	class GraphicsAPIBase;

	// this class is partially thread safe, but TODO document the functions that need to be run on the main graphics thread
	class Monitor
	{
	public:
		enum class State { connected, disconnected };
		struct GammaRamp { std::vector<unsigned short> red, green, blue; };

		// Monitor is copyable and movable, but can only be created by GraphicsAPI
		explicit Monitor(std::unique_ptr<MonitorBase> monitorBase) noexcept;
		Monitor(Monitor&& monitor) = default;
		Monitor(const Monitor&) noexcept;
		Monitor& operator=(const Monitor&) noexcept;
		Monitor& operator=(Monitor&&) noexcept;
		~Monitor() noexcept = default;

		bool operator==(const Monitor& other) const noexcept;
		bool operator!=(const Monitor& other) const noexcept;

		std::string getName() const noexcept;
		qe::Vector2i getPosition() const noexcept;
		qe::Vector2ui getPhysicalSize() const noexcept; // in mm

		qe::VideoMode getVideoMode() const noexcept;
		std::vector<qe::VideoMode> getVideoModes() const noexcept;

		// most platforms only support gamma ramps with 256 elements, this will fail silently
		bool setGammaRamp(const qe::Monitor::GammaRamp& ramp) noexcept;
		bool setGamma(float gamma) noexcept;
		qe::Monitor::GammaRamp getGammaRamp() const noexcept;

		void setMonitorCallback(std::function<void(const Monitor&, State)> callback) noexcept;

	private:
		std::unique_ptr<MonitorBase> monitorBase;

		friend GraphicsAPIBase;
		friend Window;
	};
}

#include "QENG/graphics/impl/MonitorBase.ipp"


#endif //QUESTIAENGINE_MONITOR_H
