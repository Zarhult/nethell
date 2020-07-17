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

        void setXY(int x, int y);
        void setSpriteNum(int spriteNum);
        void toggleOnscreen();

        int getSpriteNum()  const;
        int getXPos()       const;
        int getYPos()       const;
        bool isOnscreen()   const;

    private:
        SpriteSheet::SpriteSheetShPtr mSpriteSheetPtr {nullptr};    // Pointer to sprite sheet associated with this sprite
        int mSpriteNum {0};                                         // Its number in the sprite sheet
        int mXPos {0};
        int mYPos {0};

        bool mIsOnscreen {false};
};

#endif
