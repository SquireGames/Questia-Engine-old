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
