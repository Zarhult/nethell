#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include "texture.hpp"

class SpriteSheet
{
    public:
	using SpriteSheetPtr = std::unique_ptr<SpriteSheet>;

    public:
	SpriteSheet() {} 
	~SpriteSheet();

    private:
	Texture::TexturePtr sheetTexture {nullptr};

};

#endif
