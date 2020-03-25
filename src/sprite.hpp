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
	    : mSpriteSheetPtr(spriteSheetPtr), mSpriteNum(spriteNum) {}

	void render();

	void setXY(int x, int y);

	int getXPos() const;
	int getYPos() const;

    private:
	SpriteSheet::SpriteSheetShPtr mSpriteSheetPtr {nullptr};    // Pointer to sprite sheet associated with this sprite
	int mSpriteNum	{0};					    // Its number in the sprite sheet
	int mXPos	{0};
	int mYPos	{0};
};

#endif
