#ifndef QUESTIAENGINE_WINDOWBASE_H
#define QUESTIAENGINE_WINDOWBASE_H

namespace qe
{
	class WindowBase
	{
	public:
		virtual ~WindowBase() noexcept = default;
		virtual void display() noexcept = 0;
		virtual void toFullScreen() noexcept = 0;

		virtual void toWindowed(unsigned int width, unsigned int height) noexcept = 0;
		virtual void resize(unsigned int width, unsigned int height) noexcept = 0;
		virtual void setTitle(const std::string& title) noexcept = 0;

		virtual unsigned int getWidth() const noexcept = 0;
		virtual unsigned int getHeight() const noexcept = 0;
		virtual WindowMode getMode() const noexcept = 0;

		virtual bool shouldClose() const noexcept = 0;
		virtual void resetShouldClose() noexcept = 0;

	protected:
		explicit WindowBase(GraphicsAPIBase* pAPI) noexcept;
		GraphicsAPIBase* const pAPI;
	};

}

#endif //QUESTIAENGINE_WINDOWBASE_H