#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include "spritesheet.hpp"
#include "sprite.hpp"
#include "sdlw.hpp"

class Game
{
    public:
	Game(int winWidth, int winHeight);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	/* Game Functions */

	// Sprite sheets contain each frame of an animation for a single entity, or a sheet of various static sprites, but never a combination.
	bool loadSpriteSheet(const std::string &path, int spriteWidth, int spriteHeight, int spritesX, int spritesY);
	void eventHandle();					// Process an event
	void render();						// Render all onscreen sprites
	void moveSprite(int spriteVecPos, int xPos, int yPos);	// Set a sprite's x and y positions
	void changeSprite(int spriteVecPos, int newSpriteNum);	// Change sprite number with respect to its sprite sheet - useful for rendering animation
	void toggleSprite(int spriteVecPos);			// Toggle sprite rendering - sprites are considered offscreen when first created

	/* Accessors */

	int getSpriteNum(int spriteVecPos)	    const;
	int getSpriteXPos(int spriteVecPos)	    const;
	int getSpriteYPos(int spriteVecPos)	    const;
	bool getSpriteIsOnscreen(int spriteVecPos)  const;
	bool getRunStatus()			    const;

	/* Sprite Enumerations */

	// First comes all animated sprites, followed by an enum for each sheet of static sprites. Static sprites can easily be set to any sprite in
	//	their respective sprite sheet with the changeSprite function.
	// Matches order of sprites in sprite sheet, starting from 0.
	enum SpriteName
	{
	    PLAYER
	};
	
	// The rest of the enumerations define the frames of a sprite's animation(s) or the elements of a static sprite sheet, 0 being the first 
	//	sprite of its sprite sheet, 1 the next, etc.
	// Should only be used as the second argument in the changeSprite function.
	enum SpritePlayerFrames
	{
	    PLAYER_IDLE,
	    PLAYER_WALK
	};

    private:
	sdlw::WindowShPtr mWindow {nullptr};
	sdlw::RendererShPtr mRenderer {nullptr};
	std::vector<SpriteSheet::SpriteSheetShPtr> mSpriteSheetVec {nullptr};
	std::vector<Sprite::SpriteShPtr> mSpriteVec;
	SDL_Event mEvent;

	bool mIsRunning {false};
};

#endif
