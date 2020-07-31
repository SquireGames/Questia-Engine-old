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

		// MonitorImpl is copyable and movable, but can only be created by GraphicsAPIImpl
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


#include "QENG/graphics/impl/MonitorBase.h"

namespace qe
{
	inline MonitorBase::MonitorBase(GraphicsAPIBase* pAPI) noexcept : pAPI(pAPI)
	{

	}

	inline Monitor::Monitor(std::unique_ptr<MonitorBase> monitorBase) noexcept : monitorBase(std::move(monitorBase))
	{
	}

	inline Monitor::Monitor(const Monitor& m) noexcept : monitorBase(std::move(m.monitorBase->clone()))
	{
	}

	inline std::string Monitor::getName() const noexcept
	{
		return monitorBase->getName();
	}

	inline void Monitor::setMonitorCallback(std::function<void(const Monitor&, Monitor::State)> callback) noexcept
	{
		monitorBase->setMonitorCallback(std::move(callback));
	}

	inline bool Monitor::operator==(const Monitor& other) const noexcept
	{
		return monitorBase->operator==(other.monitorBase.get());
	}

	inline bool Monitor::operator!=(const Monitor& other) const noexcept
	{
		return !Monitor::operator==(other);
	}

	inline qe::Vector2i Monitor::getPosition() const noexcept
	{
		return monitorBase->getPosition();
	}

	inline qe::Vector2ui Monitor::getPhysicalSize() const noexcept
	{
		return monitorBase->getPhysicalSize();
	}

	inline qe::VideoMode Monitor::getVideoMode() const noexcept
	{
		return monitorBase->getVideoMode();
	}

	inline std::vector<qe::VideoMode> Monitor::getVideoModes() const noexcept
	{
		return monitorBase->getVideoModes();
	}

	inline qe::Monitor::GammaRamp Monitor::getGammaRamp() const noexcept
	{
		return monitorBase->getGammaRamp();
	}

	inline bool Monitor::setGammaRamp(const qe::Monitor::GammaRamp& ramp) noexcept
	{
		return monitorBase->setGammaRamp(ramp);
	}

	inline bool Monitor::setGamma(float gamma) noexcept
	{
		return monitorBase->setGamma(gamma);
	}

	inline Monitor& Monitor::operator=(const Monitor& m) noexcept
	{
		this->monitorBase = std::unique_ptr<MonitorBase>(m.monitorBase->clone());
		return *this;
	}

	inline Monitor& Monitor::operator=(Monitor&& m) noexcept
	{
		this->monitorBase = std::move(m.monitorBase);
		return *this;
	}

	inline void* MonitorBase::getMonitorHandle() const noexcept
	{
		return nullptr;
	}
}

#endif //QUESTIAENGINE_MONITOR_H
