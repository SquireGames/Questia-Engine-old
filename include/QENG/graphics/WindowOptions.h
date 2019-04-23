#ifndef QUESTIAENGINE_WINDOWOPTIONS_H
#define QUESTIAENGINE_WINDOWOPTIONS_H

#include <variant>

#include "QENG/graphics/VideoMode.h"

namespace qe
{
	struct WindowOptions
	{
		struct Windowed
		{
			explicit Windowed(bool resizable = true, bool initiallyVisible = true, bool initiallyFocused = true
					, bool initiallyMaximized = false, bool alwaysOnTop = false) noexcept:
					resizable(resizable), initiallyVisible(initiallyVisible), initiallyFocused(initiallyFocused),
					initiallyMaximized(initiallyMaximized), alwaysOnTop(alwaysOnTop)
			{}
			bool resizable : 1;
			bool initiallyVisible : 1;
			bool initiallyFocused : 1;
			bool initiallyMaximized : 1;
			bool alwaysOnTop : 1;
		};
		struct Fullscreen
		{
			explicit Fullscreen(bool centerCursor = false, bool autoIconify = true) :
					center_cursor(centerCursor), auto_iconify(autoIconify)
			{}
			bool center_cursor : 1;
			bool auto_iconify : 1;
		};

		// ctor
		explicit WindowOptions(VideoMode videoMode, Windowed options) :
				specificOptions(options), videoMode(videoMode)
		{}
		explicit WindowOptions(VideoMode videoMode, Fullscreen options) :
				specificOptions(options), videoMode(videoMode)
		{}

		std::variant<Windowed, Fullscreen> specificOptions;
		VideoMode videoMode;
	};
}

#endif //QUESTIAENGINE_WINDOWOPTIONS_H
