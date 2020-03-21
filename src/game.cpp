#include <iostream>
#include <vector>
#include <memory>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.hpp"
#include "texture.hpp"

Game::Game(const int &winWidth, const int &winHeight)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
	throw std::runtime_error(SDL_GetError());
    }
    else
    {
	window.reset(SDL_CreateWindow("Nethell", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight, SDL_WINDOW_SHOWN));
	if (window == nullptr) 
	{
	    throw std::runtime_error(SDL_GetError());
	} 
	else 
	{
	    renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));
	    if (renderer == nullptr)
	    {
		throw std::runtime_error(SDL_GetError());
	    }
	    else
	    {
		SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);

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

bool Game::loadTexture(const std::string &path, const int &xPos, const int &yPos)
{
    Texture::TexturePtr pTexture {std::make_unique<Texture>(xPos, yPos)};
    bool success {pTexture->loadFromFile(renderer, path)};

    if (success)
    {
	textureVec.push_back(std::move(pTexture));
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
    SDL_RenderClear(renderer.get());

    for (unsigned int i = 0; i < textureVec.size(); ++i)
    {
	assert(textureVec.at(i));

	textureVec.at(i)->render(renderer, nullptr, textureVec.at(i)->getXPos(), textureVec.at(i)->getYPos());
    }

    SDL_RenderPresent(renderer.get());
}

const bool& Game::getRunStatus() const
{
    return isRunning;
}
