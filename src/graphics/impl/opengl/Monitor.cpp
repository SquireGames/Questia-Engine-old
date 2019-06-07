#include "QENG/graphics/impl/opengl/Monitor.h"
#include "QENG/graphics/impl/opengl/Window.h"
#include <mutex>
#include <vector>

namespace qe::gl
{
	static std::mutex monitorLock;
	static int monitorRefCount = 0;
	static std::function<void(const qe::Monitor&, qe::Monitor::State)> monitorConnectionCallback = {};
	static GraphicsAPIBase* pAPIShared = nullptr;

	Monitor::Monitor(GraphicsAPIBase* pAPI, GLFWmonitor* pMonitor) noexcept
		: MonitorBase(pAPI), pMonitor(pMonitor), monitorName(std::string(glfwGetMonitorName(pMonitor)))
	{
		std::lock_guard<std::mutex> lock(monitorLock);
		// if this is the first initialized Monitor object
		if(monitorRefCount == 0)
		{
			glfwSetMonitorCallback(Monitor::monitorCallback);
			pAPIShared= this->pAPI;
		}
		monitorRefCount++;
	}

    Monitor::~Monitor() noexcept
	{
		std::lock_guard<std::mutex> lock(monitorLock);
		monitorRefCount--;
		if (monitorRefCount == 0)
		{
			pAPIShared = nullptr;
		}
	}

	std::string Monitor::getName() const noexcept
	{
		return monitorName;
	}

	void Monitor::monitorCallback(GLFWmonitor* pMonitor, int event)
	{
		// only call the callback if the callback was set
		{
			std::lock_guard<std::mutex> lock(monitorLock);
			if (!monitorConnectionCallback) {
				return;
			}
		}
		// ctor must not be locked because the constructor locks with the same mutex
		qe::Monitor monitor = qe::Monitor(std::unique_ptr<MonitorBase>(new qe::gl::Monitor(pAPIShared, pMonitor)));

		std::lock_guard<std::mutex> lock(monitorLock);
		if (event == GLFW_CONNECTED)
		{
			monitorConnectionCallback(monitor, qe::Monitor::State::connected);
		}
		else if (event == GLFW_DISCONNECTED)
		{
			monitorConnectionCallback(monitor, qe::Monitor::State::disconnected);
		}
	}

	void Monitor::setMonitorCallback(std::function<void(const qe::Monitor&, qe::Monitor::State)> callback) const noexcept
	{
		std::lock_guard<std::mutex> lock(monitorLock);
		qe::gl::monitorConnectionCallback = callback;
	}

	bool Monitor::operator==(MonitorBase* other) const noexcept
	{
		return pMonitor == other->getMonitorHandle();
	}

	void* Monitor::getMonitorHandle() const noexcept
	{
		return pMonitor;
	}

	Vector2i Monitor::getPosition() const noexcept
	{
		int xpos, ypos;
		glfwGetMonitorPos(pMonitor, &xpos, &ypos);
		return Vector2i{xpos, ypos};
	}

	Vector2ui Monitor::getPhysicalSize() const noexcept
	{
		int xmm, ymm;
		glfwGetMonitorPhysicalSize(pMonitor, &xmm, &ymm);
		return qe::Vector2ui(static_cast<unsigned int>(xmm), static_cast<unsigned int>(ymm));
	}

	VideoMode Monitor::getVideoMode() const noexcept
	{
		const GLFWvidmode* videoMode = glfwGetVideoMode(pMonitor);
		return {static_cast<unsigned int>(videoMode->width), static_cast<unsigned int>(videoMode->height), static_cast<unsigned int>(videoMode->refreshRate)
		        , static_cast<unsigned int>(videoMode->redBits), static_cast<unsigned int>(videoMode->greenBits), static_cast<unsigned int>(videoMode->blueBits)};
	}

	std::vector<VideoMode> Monitor::getVideoModes() const noexcept
	{
		int modeCount;
		const GLFWvidmode* videoModes = glfwGetVideoModes(pMonitor, &modeCount);
		std::vector<VideoMode> modes;
		modes.reserve(modeCount);
		for(unsigned int i = 0; i < static_cast<unsigned int>(modeCount); i++)
		{
			modes.emplace_back(VideoMode{static_cast<unsigned int>(videoModes[i].width), static_cast<unsigned int>(videoModes[i].height)
			                             , static_cast<unsigned int>(videoModes[i].refreshRate), static_cast<unsigned int>(videoModes[i].redBits)
			                             , static_cast<unsigned int>(videoModes[i].greenBits), static_cast<unsigned int>(videoModes[i].blueBits)});
		}
		return modes;
	}

	qe::Monitor::GammaRamp Monitor::getGammaRamp() const noexcept
	{
		const GLFWgammaramp* pRamp = glfwGetGammaRamp(pMonitor);
		unsigned int size = pRamp->size;
		qe::Monitor::GammaRamp ramp;
		ramp.red.reserve(size);
		ramp.green.reserve(size);
		ramp.blue.reserve(size);
		for(unsigned int i = 0; i < size; i++)
		{
			ramp.red.emplace_back(pRamp->red[i]);
		}
		for(unsigned int i = 0; i < size; i++)
		{
			ramp.green.emplace_back(pRamp->green[i]);
		}
		for(unsigned int i = 0; i < size; i++)
		{
			ramp.blue.emplace_back(pRamp->blue[i]);
		}
		return ramp;
	}

	std::unique_ptr<MonitorBase> Monitor::clone() const noexcept
	{
		return std::unique_ptr<MonitorBase>(dynamic_cast<MonitorBase*>(new Monitor(pAPI, pMonitor)));
	}

	bool Monitor::setGammaRamp(const qe::Monitor::GammaRamp& ramp) noexcept
	{
		const unsigned int redSize = static_cast<int>(ramp.red.size());
		const unsigned int greenSize = static_cast<int>(ramp.red.size());
		const unsigned int blueSize = static_cast<int>(ramp.blue.size());
		if(redSize != greenSize || greenSize != blueSize)
		{
			return false;
		}
		const GLFWgammaramp glfwRamp {const_cast<unsigned short*>(ramp.red.data()), const_cast<unsigned short*>(ramp.green.data())
									, const_cast<unsigned short*>(ramp.blue.data()), redSize};
		// fails silently
		glfwSetGammaRamp(pMonitor, &glfwRamp);
		return true;
	}

	bool Monitor::setGamma(float gamma) noexcept
	{
		if(gamma <= 0)
		{
			return false;
		}
		glfwSetGamma(pMonitor, gamma);
		return true;
	}
}
