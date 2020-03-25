#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include <memory>
#include <SDL2/SDL.h>
#include "texture.hpp"
#include "sdlw.hpp"

class SpriteSheet : public Texture
{
    public:
	using SpriteSheetShPtr = std::shared_ptr<SpriteSheet>;

    public:
	SpriteSheet(sdlw::RendererShPtr texRenderer, int spriteWidth, int spriteHeight, int spritesX, int spritesY) 
		    : Texture(texRenderer), spriteWidth(spriteWidth), spriteHeight(spriteHeight), spritesX(spritesX), spritesY(spritesY) {} 

	int getSpriteWidth()  const;
	int getSpriteHeight() const;
	int getSpritesX()     const;
	int getSpritesY()     const;

    private:
	int spriteWidth	 {0};
	int spriteHeight {0};
	int spritesX	 {0};
	int spritesY	 {0};
};

#endif
