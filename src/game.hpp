#ifndef GAME_HPP
#define GAME_HPP

#include "spritesheet.hpp"
#include "sprite.hpp"
#include "sdlw.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <vector>
#include <memory>

class Game
{
    public:
	Game(int winWidth, int winHeight);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	~Game();

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

    private:
	sdlw::WindowShPtr mWindow {nullptr};
	sdlw::RendererShPtr mRenderer {nullptr};
	std::vector<SpriteSheet::SpriteSheetShPtr> mSpriteSheetVec;
	std::vector<Sprite::SpriteShPtr> mSpriteVec;
	SDL_Event mEvent;
	TTF_Font* gameFont;

	bool mIsRunning {false};
};

#endif
