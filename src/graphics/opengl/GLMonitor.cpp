#include "QENG/graphics/opengl/GLMonitor.h"
#include <mutex>
#include <vector>
#include "QENG/graphics/opengl/GLWindow.h"

namespace qe
{
	static std::mutex monitorLock;
	static int monitorRefCount = 0;
	static std::function<void(const Monitor&, Monitor::State)> monitorConnectionCallback = {};

	GLMonitor::GLMonitor(GLFWmonitor* pMonitor) noexcept
		: MonitorBase(), pMonitor(pMonitor), monitorName(std::string(glfwGetMonitorName(pMonitor)))
	{
		std::lock_guard<std::mutex> lock(monitorLock);
		// if this is the first initialized GLMonitor object
		if(monitorRefCount == 0)
		{
			glfwSetMonitorCallback(GLMonitor::monitorCallback);
		}
		monitorRefCount++;
	}

    GLMonitor::~GLMonitor() noexcept
	{
		std::lock_guard<std::mutex> lock(monitorLock);
		monitorRefCount--;
	}

	std::string GLMonitor::getName() const noexcept
	{
		return monitorName;
	}

	void GLMonitor::monitorCallback(GLFWmonitor* pMonitor, int event)
	{
		// only call the callback if the callback was set
		{
			std::lock_guard<std::mutex> lock(monitorLock);
			if (!monitorConnectionCallback) {
				return;
			}
		}
		// ctor must not be locked because the constructor locks with the same mutex
		Monitor monitor = Monitor(std::unique_ptr<MonitorBase>(new GLMonitor(pMonitor)));

		std::lock_guard<std::mutex> lock(monitorLock);
		if (event == GLFW_CONNECTED)
		{
			monitorConnectionCallback(monitor, Monitor::State::connected);
		}
		else if (event == GLFW_DISCONNECTED)
		{
			monitorConnectionCallback(monitor, Monitor::State::disconnected);
		}
	}

	void GLMonitor::setMonitorCallback(std::function<void(const Monitor&, Monitor::State)> callback) const noexcept
	{
		std::lock_guard<std::mutex> lock(monitorLock);
		qe::monitorConnectionCallback = callback;
	}

	bool GLMonitor::operator==(MonitorBase* other) const noexcept
	{
		return pMonitor == other->getMonitorHandle();
	}

	void* GLMonitor::getMonitorHandle() const noexcept
	{
		return pMonitor;
	}

	Vector2i GLMonitor::getPosition() const noexcept
	{
		int xpos, ypos;
		glfwGetMonitorPos(pMonitor, &xpos, &ypos);
		return Vector2i{xpos, ypos};
	}

	Vector2ui GLMonitor::getPhysicalSize() const noexcept
	{
		int xmm, ymm;
		glfwGetMonitorPhysicalSize(pMonitor, &xmm, &ymm);
		return qe::Vector2ui(static_cast<unsigned int>(xmm), static_cast<unsigned int>(ymm));
	}

	Monitor::VideoMode GLMonitor::getVideoMode() const noexcept
	{
		const GLFWvidmode* videoMode = glfwGetVideoMode(pMonitor);
		return {static_cast<unsigned int>(videoMode->width), static_cast<unsigned int>(videoMode->height), static_cast<unsigned int>(videoMode->redBits)
		        , static_cast<unsigned int>(videoMode->greenBits), static_cast<unsigned int>(videoMode->blueBits), static_cast<unsigned int>(videoMode->refreshRate)};
	}

	std::vector<Monitor::VideoMode> GLMonitor::getVideoModes() const noexcept
	{
		int modeCount;
		const GLFWvidmode* videoModes = glfwGetVideoModes(pMonitor, &modeCount);
		std::vector<Monitor::VideoMode> modes;
		modes.reserve(modeCount);
		for(unsigned int i = 0; i < static_cast<unsigned int>(modeCount); i++)
		{
			modes.emplace_back(Monitor::VideoMode{static_cast<unsigned int>(videoModes[i].width), static_cast<unsigned int>(videoModes[i].height)
					             , static_cast<unsigned int>(videoModes[i].redBits), static_cast<unsigned int>(videoModes[i].greenBits)
					             , static_cast<unsigned int>(videoModes[i].blueBits), static_cast<unsigned int>(videoModes[i].refreshRate)});
		}
		return modes;
	}

	Monitor::GammaRamp GLMonitor::getGammaRamp() const noexcept
	{
		const GLFWgammaramp* pRamp = glfwGetGammaRamp(pMonitor);
		unsigned int size = pRamp->size;
		Monitor::GammaRamp ramp;
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

	std::unique_ptr<MonitorBase> GLMonitor::clone() const noexcept
	{
		return std::unique_ptr<MonitorBase>(reinterpret_cast<MonitorBase*>(new GLMonitor(pMonitor)));
	}

	bool GLMonitor::setGammaRamp(const qe::Monitor::GammaRamp& ramp) noexcept
	{
		const int redSize = static_cast<int>(ramp.red.size());
		const int greenSize = static_cast<int>(ramp.red.size());
		const int blueSize = static_cast<int>(ramp.blue.size());
		if(redSize != greenSize || greenSize != blueSize)
		{
			return false;
		}
		const GLFWgammaramp glfwRamp {const_cast<unsigned short*>(ramp.red.data()), const_cast<unsigned short*>(ramp.green.data())
									, const_cast<unsigned short*>(ramp.blue.data()), static_cast<unsigned int>(redSize)};
		// fails silently
		glfwSetGammaRamp(pMonitor, &glfwRamp);
		return true;
	}

	bool GLMonitor::setGamma(float gamma) noexcept
	{
		if(gamma <= 0)
		{
			return false;
		}
		glfwSetGamma(pMonitor, gamma);
		return true;
	}

	std::function<WindowBase*(const std::string&, unsigned int, unsigned int, const Monitor&)> GLMonitor::getWindowConstructor() const noexcept
	{
		return [](const std::string& name, unsigned int width, unsigned int height, const Monitor& monitor) {return new GLWindow(name, width, height, monitor);};
	}
}
