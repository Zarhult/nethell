#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <memory>
#include "spritesheet.hpp"

class Sprite
{
    public:
	using SpriteShPtr = std::shared_ptr<Sprite>;

    public:
	Sprite(SpriteSheet::SpriteSheetShPtr spriteSheetPtr, int spriteNum)
	    : spriteSheetPtr(spriteSheetPtr), spriteNum(spriteNum) {}

	void render();

	void setXY(int x, int y);

	int getXPos() const;
	int getYPos() const;

    private:
	SpriteSheet::SpriteSheetShPtr spriteSheetPtr {nullptr};	// Pointer to sprite sheet associated with this sprite
	int spriteNum {0};					// Its number in the sprite sheet
	int xPos {0};
	int yPos {0};
};

#endif
