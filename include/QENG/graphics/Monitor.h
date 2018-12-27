#ifndef QUESTIAENGINE_MONITOR_H
#define QUESTIAENGINE_MONITOR_H

#include <memory>
#include <string>

namespace qe
{
	class MonitorBase;

	class Monitor
	{
	public:
		explicit Monitor(std::unique_ptr<MonitorBase> monitorBase) noexcept;
		~Monitor() noexcept = default;
		Monitor(Monitor&& monitor) = default;

		std::string getMonitorName();

	private:
		std::unique_ptr<MonitorBase> monitorBase;
	};




	class MonitorBase
	{
	public:
		virtual ~MonitorBase() noexcept = default;
		virtual std::string getMonitorName() = 0;

	protected:
		explicit MonitorBase() noexcept = default;

	};

	inline Monitor::Monitor(std::unique_ptr<MonitorBase> monitorBase) noexcept : monitorBase(std::move(monitorBase))
	{
	}

	inline std::string Monitor::getMonitorName()
	{
		return monitorBase->getMonitorName();
	}

}

#endif //QUESTIAENGINE_MONITOR_H
