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
    SpriteSheet(sdlw::RendererShPtr renderer, bool isAnimation, int spriteWidth, int spriteHeight, int spritesX, int spritesY) 
        : Texture(renderer), mIsAnimation(isAnimation), mSpriteWidth(spriteWidth), mSpriteHeight(spriteHeight), 
          mSpritesX(spritesX), mSpritesY(spritesY) {} 
    
    bool isAnimation()    const;
    int getSpriteWidth()  const;
    int getSpriteHeight() const;
    int getSpritesX()     const;
    int getSpritesY()     const;
    
private:
    bool mIsAnimation   {false}; // Whether this is a sheet of animation frames, or various static sprites
    int mSpriteWidth    {0};
    int mSpriteHeight   {0};
    int mSpritesX       {0};
    int mSpritesY       {0};
};

#endif
