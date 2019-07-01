#ifndef QUESTIAENGINE_MONITORBASE_H
#define QUESTIAENGINE_MONITORBASE_H

namespace qe
{
	class GraphicsAPIBase;

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

		virtual std::unique_ptr<MonitorBase> clone() const noexcept = 0;

		GraphicsAPIBase* const pAPI;

	protected:
		explicit MonitorBase(GraphicsAPIBase* pAPI) noexcept;
	};

}


#endif //QUESTIAENGINE_MONITORBASE_H
