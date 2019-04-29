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
	class WindowBase;
	class Window;

	// this class is partially thread safe, but TODO document the functions that need to be run on the main graphics thread
	class Monitor
	{
	public:
		enum class State {connected, disconnected};
		struct GammaRamp { std::vector<unsigned short> red, green, blue;};

		// Monitor is copyable and movable
		// TODO assert() that moved Monitors are not being used in Debug mode
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
		// in mm
		qe::Vector2ui getPhysicalSize() const noexcept;

		qe::VideoMode getVideoMode() const noexcept;
		std::vector<qe::VideoMode> getVideoModes() const noexcept;

		qe::Monitor::GammaRamp getGammaRamp() const noexcept;
		// most platforms only support gamma ramps with 256 elements, this will fail silently if it fails for that reason
		bool setGammaRamp(const qe::Monitor::GammaRamp& ramp) noexcept;
		bool setGamma(float gamma) noexcept;

		void setMonitorCallback(std::function<void(const Monitor&, State)> callback) noexcept;

		MonitorBase* getMonitorPtr() const noexcept;

	private:
		friend Window;
		std::function<WindowBase *(const std::string&, const WindowOptions&, const Monitor&, const Window*)> getWindowConstructor() const noexcept;

		std::unique_ptr<MonitorBase> monitorBase;
	};



	class MonitorBase
	{
	public:
		virtual ~MonitorBase() noexcept = default;

		virtual std::string getName() const noexcept = 0;
		virtual Vector2i getPosition() const noexcept = 0;
		virtual Vector2ui getPhysicalSize() const noexcept = 0;

		virtual bool operator==(MonitorBase* other) const noexcept = 0;

		virtual void setMonitorCallback(std::function<void(const Monitor& monitor, Monitor::State state)> callback) const noexcept = 0;

		virtual void* getMonitorHandle() const noexcept;

		virtual qe::VideoMode getVideoMode() const noexcept = 0;
		virtual std::vector<qe::VideoMode> getVideoModes() const noexcept = 0;

		virtual qe::Monitor::GammaRamp getGammaRamp() const noexcept = 0;
		virtual bool setGammaRamp(const qe::Monitor::GammaRamp& ramp) noexcept = 0;
		virtual bool setGamma(float gamma) noexcept = 0;

		virtual std::function<WindowBase*(const std::string&, const WindowOptions&, const Monitor&, const Window*)> getWindowConstructor() const noexcept = 0;
		virtual std::unique_ptr<MonitorBase> clone() const noexcept = 0;
	protected:
		explicit MonitorBase() noexcept = default;
	};

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

	inline std::function<WindowBase *(const std::string&, const WindowOptions&, const Monitor&, const Window*)> Monitor::getWindowConstructor() const noexcept
	{
		return monitorBase->getWindowConstructor();
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

	inline MonitorBase* Monitor::getMonitorPtr() const noexcept
	{
		return monitorBase.get();
	}

	inline void* MonitorBase::getMonitorHandle() const noexcept
	{
		return nullptr;
	}
}

#endif //QUESTIAENGINE_MONITOR_H
