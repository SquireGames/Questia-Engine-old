#ifndef QUESTIAENGINE_VIDEOMODE_H
#define QUESTIAENGINE_VIDEOMODE_H

namespace qe
{
	struct VideoMode
	{
		VideoMode(unsigned int width, unsigned int height, unsigned int refreshRate = 0) :
				width(width), height(height), refreshRate(refreshRate), redBits(0), greenBits(0), blueBits(0)
		{}
		VideoMode(unsigned int width, unsigned int height, unsigned int refreshRate
				, unsigned int redBits, unsigned int greenBits, unsigned int blueBits) :
				width(width), height(height), refreshRate(refreshRate), redBits(redBits), greenBits(greenBits), blueBits(blueBits)
		{}

		unsigned int width, height, refreshRate, redBits, greenBits, blueBits;
	};
}

#endif //QUESTIAENGINE_VIDEOMODE_H
