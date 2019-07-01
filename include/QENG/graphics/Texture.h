#ifndef QUESTIAENGINE_TEXTURE_H
#define QUESTIAENGINE_TEXTURE_H

#include <memory>
#include <string>

namespace qe
{
	class TextureBase;

	class Texture
	{
	public:
		explicit Texture(std::string fileName);
		constexpr Texture();

	private:
		std::unique_ptr<TextureBase> textureBase;
	};
}

#include "QENG/graphics/impl/TextureBase.h"



#endif //QUESTIAENGINE_TEXTURE_H
