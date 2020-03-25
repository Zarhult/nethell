#include <iostream>
#include <vector>
#include <memory>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.hpp"
#include "texture.hpp"

Game::Game(int winWidth, int winHeight)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
	throw std::runtime_error(SDL_GetError());
    }
    else
    {
	mWindow.reset(SDL_CreateWindow("Nethell", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight, SDL_WINDOW_SHOWN));
	if (mWindow == nullptr) 
	{
	    throw std::runtime_error(SDL_GetError());
	} 
	else 
	{
	    mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	    if (mRenderer == nullptr)
	    {
		throw std::runtime_error(SDL_GetError());
	    }
	    else
	    {
		SDL_SetRenderDrawColor(mRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);

		// Initialize JPG loading
		int imgFlags {IMG_INIT_JPG};
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
		    throw std::runtime_error(IMG_GetError());
		} 
		else // If all initialized successfuly
		{
		    isRunning = true;
		}
	    }
	}
    }
}

bool Game::loadSpriteSheet(const std::string &path, int spriteWidth, int spriteHeight, int spritesX, int spritesY)
{
    SpriteSheet::SpriteSheetShPtr spriteSheet {std::make_shared<SpriteSheet>(mRenderer, spriteWidth, spriteHeight, spritesX, spritesY)};
    bool success {spriteSheet->loadFromFile(path)};

    if (success)
    {
	mSpriteSheet = spriteSheet;

	int totalSprites = spritesX * spritesY;

	for (int i = 0; i < totalSprites; ++i)
	{
	    // i is sprite num
	    Sprite::SpriteShPtr newSprite(std::make_shared<Sprite>(spriteSheet, i));
	    spriteVec.push_back(std::move(newSprite));
	}
    }
    else
    {
	std::cerr << "Failed to load file into sprite sheet." << std::endl;
    }

    return success;
}

void Game::eventHandle()
{
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
    {
	isRunning = false;
    }
}

void Game::render()
{
    SDL_RenderClear(mRenderer.get());

    for (unsigned int i = 0; i < spriteVec.size(); ++i)
    {
	assert(spriteVec.at(i));

	spriteVec.at(i)->render();
    }

    SDL_RenderPresent(mRenderer.get());
}

void Game::moveSprite(int spriteNum, int xPos, int yPos)
{
    assert(static_cast<unsigned int>(spriteNum) < spriteVec.size());

    spriteVec.at(spriteNum)->setXY(xPos, yPos);
}

int Game::getSpriteXPos(int spriteNum) const
{
    assert(static_cast<unsigned int>(spriteNum) < spriteVec.size());

    return spriteVec.at(spriteNum)->getXPos();
}

int Game::getSpriteYPos(int spriteNum) const
{
    assert(static_cast<unsigned int>(spriteNum) < spriteVec.size());

    return spriteVec.at(spriteNum)->getYPos();
}

bool Game::getRunStatus() const
{
    return isRunning;
}
