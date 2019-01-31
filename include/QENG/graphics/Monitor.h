#ifndef QUESTIAENGINE_MONITOR_H
#define QUESTIAENGINE_MONITOR_H

#include <memory>
#include <string>
#include <functional>

namespace qe
{
	class MonitorBase;

	class Monitor
	{
	public:
		enum class State {connected, disconnected};

		// Monitor is a move-only class
		explicit Monitor(std::unique_ptr<MonitorBase> monitorBase) noexcept;
		~Monitor() noexcept = default;
		Monitor(Monitor&& monitor) = default;
		Monitor(Monitor&) = delete;
		Monitor operator=(Monitor&) = delete;
		Monitor operator=(Monitor&&) = delete;

		bool operator==(const Monitor& other) const noexcept;
		bool operator!=(const Monitor& other) const noexcept;

		std::string getMonitorName() const noexcept;
		void setMonitorCallback(std::function<void(Monitor&&, State)> callback) const noexcept;

	private:
		std::unique_ptr<MonitorBase> monitorBase;
	};



	class MonitorBase
	{
	public:
		virtual ~MonitorBase() noexcept = default;
		virtual std::string getMonitorName() const noexcept = 0;
		virtual void setMonitorCallback(std::function<void(Monitor&& monitor, Monitor::State state)> callback) const noexcept = 0;

		virtual bool operator==(MonitorBase* other) const noexcept = 0;

		virtual void* getMonitorHandle() const noexcept;
	protected:
		explicit MonitorBase() noexcept = default;
	};

	inline Monitor::Monitor(std::unique_ptr<MonitorBase> monitorBase) noexcept : monitorBase(std::move(monitorBase))
	{
	}

	inline std::string Monitor::getMonitorName() const noexcept
	{
		return monitorBase->getMonitorName();
	}

	inline void Monitor::setMonitorCallback(std::function<void(Monitor&&, Monitor::State)> callback) const noexcept
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

	inline void* MonitorBase::getMonitorHandle() const noexcept
	{
		return nullptr;
	}
}

#endif //QUESTIAENGINE_MONITOR_H
