#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "spritesheet.hpp"
#include <memory>

class Sprite
{
public:
    using SpriteShPtr = std::shared_ptr<Sprite>;
    
public:
    Sprite(SpriteSheet::SpriteSheetShPtr spriteSheetPtr, int spriteNum)
        : mSpriteSheetPtr(spriteSheetPtr), mSpriteNum(spriteNum) {}
    
    void render();
    
    void shiftXY(float x, float y);
    void setAngle(double angle);
    void setFlipType(SDL_RendererFlip flipType);
    void setSpriteNum(int spriteNum);
    void toggleOnscreen();
    
    int getSpriteNum()             const;
    int getXPos()                  const;
    int getYPos()                  const;
    double getAngle()              const;
    SDL_RendererFlip getFlipType() const;
    bool isOnscreen()              const;
    
private:
    SpriteSheet::SpriteSheetShPtr mSpriteSheetPtr {nullptr};    // Pointer to sprite sheet associated with this sprite
    int mSpriteNum {0};                                         // Its number in the sprite sheet
    double mAngle {0.0};
    SDL_RendererFlip mFlipType {SDL_FLIP_NONE};
    float mXPos {0.0};
    float mYPos {0.0};
    bool mIsOnscreen {false};
};

#endif
