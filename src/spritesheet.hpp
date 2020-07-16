#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include "texture.hpp"
#include "sdlw.hpp"
#include "SDL2/SDL.h"
#include <memory>

class SpriteSheet : public Texture
{
    public:
        using SpriteSheetShPtr = std::shared_ptr<SpriteSheet>;

    public:
        SpriteSheet(sdlw::RendererShPtr texRenderer, int spriteWidth, int spriteHeight, int spritesX, int spritesY) 
            : Texture(texRenderer), mSpriteWidth(spriteWidth), mSpriteHeight(spriteHeight), mSpritesX(spritesX), mSpritesY(spritesY) {} 

        int getSpriteWidth()  const;
        int getSpriteHeight() const;
        int getSpritesX()     const;
        int getSpritesY()     const;

    private:
        int mSpriteWidth    {0};
        int mSpriteHeight   {0};
        int mSpritesX	    {0};
        int mSpritesY	    {0};
};

#endif
