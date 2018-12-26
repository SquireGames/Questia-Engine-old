#ifndef QUESTIAENGINE_MONITOR_H
#define QUESTIAENGINE_MONITOR_H

namespace qe
{
	class Monitor
	{
	public:
		virtual ~Monitor() noexcept = default;

	protected:
		explicit Monitor() noexcept = default;

	};
}

#endif //QUESTIAENGINE_MONITOR_H
