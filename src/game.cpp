#include <iostream>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.hpp"
#include "texture.hpp"

Game::~Game()
{
    clean();
}

bool Game::init(const int &winWidth, const int &winHeight)
{
    bool success {true};

    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
	std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
	success = false;
    }
    else
    {
	window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr) 
	{
	    std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
	    success = false;
	} 
	else 
	{
	    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	    if (renderer == nullptr)
	    {
		std::cout << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
		success = false;
	    }
	    else
	    {
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		// Initialize JPG loading
		int imgFlags {IMG_INIT_JPG};
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
		    std::cout << "Unable to initialize SDL_image: " << IMG_GetError() << std::endl;
		    success = false;
		} 
	    }
	}
    }

    if (success)
    {
	isRunning = true;
    }

    return success;
}

bool Game::loadTexture(const std::string &path)
{
    Texture::TexturePtr pTexture {std::make_unique<Texture>(0, 0)};
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
    SDL_RenderClear(renderer);

    for (unsigned int i = 0; i < textureVec.size(); ++i)
    {
	if (textureVec.at(i)) // If texture is still valid
	{
	    textureVec.at(i)->render(renderer, textureVec.at(i)->getXPos(), textureVec.at(i)->getYPos());
	}
	else
	{
	    std::cout << "Error: Attempted access of null element of texture vector." << std::endl;
	}
    }

    SDL_RenderPresent(renderer);
}

void Game::clean() 
{
    for (unsigned int i = 0; i < textureVec.size(); ++i)
    {
	// textureVec.at(i)->free(); // unique_ptr automatically calls destructor when game goes out of scope (?)
	textureVec.pop_back();
    }

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    isRunning = false;

    IMG_Quit();
    SDL_Quit();
}

const bool& Game::getRunStatus() const
{
    return isRunning;
}
