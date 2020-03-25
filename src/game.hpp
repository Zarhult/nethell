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

	bool loadSpriteSheet(const std::string &path, int spriteWidth, int spriteHeight, int spritesX, int spritesY);
	void eventHandle();
	void render();
	void moveSprite(int spriteNum, int xPos, int yPos);

	int getSpriteXPos(int spriteNum) const;
	int getSpriteYPos(int spriteNum) const;
	bool getRunStatus() const;

    private:
	sdlw::WindowShPtr mWindow {nullptr};
	sdlw::RendererShPtr mRenderer {nullptr};
	SpriteSheet::SpriteSheetShPtr mSpriteSheet {nullptr};
	std::vector<Sprite::SpriteShPtr> spriteVec;
	SDL_Event event;
	bool isRunning {false};
};

#endif
