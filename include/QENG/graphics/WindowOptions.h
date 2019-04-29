#ifndef QUESTIAENGINE_WINDOWOPTIONS_H
#define QUESTIAENGINE_WINDOWOPTIONS_H

#include <variant>

#include "QENG/graphics/VideoMode.h"

namespace qe
{
	enum class WindowMode { windowed, fullscreen };

	struct WindowOptions
	{
		struct Windowed
		{
			Windowed(bool resizable = true, bool initiallyVisible = true, bool initiallyFocused = true
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
			Fullscreen(bool centerCursor = false, bool autoIconify = true) :
					center_cursor(centerCursor), auto_iconify(autoIconify)
			{}
			bool center_cursor : 1;
			bool auto_iconify : 1;
		};

		// ctors
		explicit WindowOptions(VideoMode videoMode, Windowed options) :
				windowedOptions(options), fullscreenOptions(), videoMode(videoMode), initMode(WindowMode::windowed)
		{}
		explicit WindowOptions(VideoMode videoMode, Fullscreen options) :
				windowedOptions(), fullscreenOptions(options), videoMode(videoMode), initMode(WindowMode::fullscreen)
		{}
		explicit WindowOptions(VideoMode videoMode, WindowMode initMode = WindowMode::windowed, Windowed windowedOptions = {}, Fullscreen fullscreenOptions = {}) :
				windowedOptions(windowedOptions), fullscreenOptions(fullscreenOptions), videoMode(videoMode), initMode(initMode)
		{}

		Windowed windowedOptions;
		Fullscreen fullscreenOptions;
		VideoMode videoMode;
		WindowMode initMode;
	};
}

#endif //QUESTIAENGINE_WINDOWOPTIONS_H
