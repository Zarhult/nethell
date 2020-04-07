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

		// Initialize PNG loading
		int imgFlags {IMG_INIT_PNG};
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
		    throw std::runtime_error(IMG_GetError());
		} 

		// Initialize SDL_ttf
		if (TTF_Init() == -1)
		{
		    throw std::runtime_error(TTF_GetError());
		}
		
		// If all initialized successfully...
		mIsRunning = true;
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
	mSpriteSheetVec.push_back(std::move(spriteSheet));

	Sprite::SpriteShPtr newSprite(std::make_shared<Sprite>(mSpriteSheetVec.back(), 0));
	mSpriteVec.push_back(std::move(newSprite));
    }
    else
    {
	std::cerr << "Failed to load texture file into sprite sheet." << std::endl;
    }

    return success;
}

void Game::eventHandle()
{
    SDL_PollEvent(&mEvent);
    if (mEvent.type == SDL_QUIT)
    {
	mIsRunning = false;
    }
}

void Game::render()
{
    SDL_RenderClear(mRenderer.get());

    for (unsigned int i = 0; i < mSpriteVec.size(); ++i)
    {
	assert(mSpriteVec.at(i));

	if (mSpriteVec.at(i)->isOnscreen())
	{
	    mSpriteVec.at(i)->render();
	}
    }

    SDL_RenderPresent(mRenderer.get());
}

void Game::moveSprite(int spriteVecPos, int xPos, int yPos)
{
    assert(static_cast<unsigned int>(spriteVecPos) < mSpriteVec.size());

    mSpriteVec.at(spriteVecPos)->setXY(xPos, yPos);
}

void Game::changeSprite(int spriteVecPos, int newSpriteNum)
{
    assert(static_cast<unsigned int>(spriteVecPos) < mSpriteVec.size());
    // TODO: assert that newSpriteNum is within bounds of the spritesheet associated with sprite

    mSpriteVec.at(spriteVecPos)->setSpriteNum(newSpriteNum);
}

void Game::toggleSprite(int spriteVecPos)
{
    assert(static_cast<unsigned int>(spriteVecPos) < mSpriteVec.size());

    mSpriteVec.at(spriteVecPos)->toggleOnscreen();
}

int Game::getSpriteNum(int spriteVecPos) const
{
    assert(this);
    assert(static_cast<unsigned int>(spriteVecPos) < mSpriteVec.size());

    return mSpriteVec.at(spriteVecPos)->getSpriteNum();
}

int Game::getSpriteXPos(int spriteVecPos) const
{
    assert(this);
    assert(static_cast<unsigned int>(spriteVecPos) < mSpriteVec.size());

    return mSpriteVec.at(spriteVecPos)->getXPos();
}

int Game::getSpriteYPos(int spriteVecPos) const
{
    assert(this);
    assert(static_cast<unsigned int>(spriteVecPos) < mSpriteVec.size());

    return mSpriteVec.at(spriteVecPos)->getYPos();
}

bool Game::getSpriteIsOnscreen(int spriteVecPos) const
{
    assert(this);
    assert(static_cast<unsigned int>(spriteVecPos) < mSpriteVec.size());

    return mSpriteVec.at(spriteVecPos)->isOnscreen();
}

bool Game::getRunStatus() const
{
    assert(this);

    return mIsRunning;
}
