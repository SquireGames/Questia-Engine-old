#ifndef QUESTIAENGINE_TEXTUREMANAGER_H
#define QUESTIAENGINE_TEXTUREMANAGER_H

#include <memory>
#include "GraphicsAPI.h"
#include "Texture.h"

namespace qe
{
	class TextureManagerBase;

	class TextureManager
	{
	public:
		// move only class
		explicit TextureManager(GraphicsAPI& api) noexcept;
		// delayed initialization with create function
		constexpr TextureManager() noexcept = default;
		TextureManager(const TextureManager&) = delete;
		TextureManager(TextureManager&&) noexcept = default;
		TextureManager& operator=(TextureManager) noexcept = delete;
		TextureManager& operator=(TextureManager&&) noexcept = default;
		~TextureManager() noexcept = default;

		// preferably use the regular constructor to this function
		void init(GraphicsAPI& api) noexcept;



	private:
		std::unique_ptr<TextureManagerBase> textureManagerBase;
	};

}


#include "QENG/graphics/impl/TextureManagerBase.h"

namespace qe
{
	qe::TextureManager::TextureManager(qe::GraphicsAPI& api) noexcept
	{

	}

	void TextureManager::init(GraphicsAPI& api) noexcept
	{

	}
}


#endif //QUESTIAENGINE_TEXTUREMANAGER_H
