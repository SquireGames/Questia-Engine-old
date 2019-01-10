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

		std::string getMonitorName() const noexcept;
		bool isConnected() const noexcept;

	private:
		std::unique_ptr<MonitorBase> monitorBase;
	};




	class MonitorBase
	{
	public:
		virtual ~MonitorBase() noexcept = default;
		virtual std::string getMonitorName() const noexcept = 0;
		virtual bool isConnected() const noexcept = 0;

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

	inline bool Monitor::isConnected() const noexcept
	{
		return monitorBase->isConnected();
	}

}

#endif //QUESTIAENGINE_MONITOR_H
