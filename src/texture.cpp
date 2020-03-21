#include <iostream>
#include <memory>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.hpp"

bool Texture::loadFromFile(sdlw::RendererShPtr renderer, const std::string &path)
{
    assert(renderer);

    // Reset if existing texture
    if (texture)
    {
	texture.reset();
	width = 0;
	height = 0;
    }

    bool success {true};

    SDL_Surface* loadedSurface { IMG_Load(path.c_str()) };
    if (loadedSurface == nullptr)
    {
	std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
	success = false;
    }
    else
    {
	texture.reset(SDL_CreateTextureFromSurface(renderer.get(), loadedSurface));
	if (texture == nullptr)
	{
	    std::cerr << "SDL_CreateTextureFromSurface error: " << SDL_GetError() << std::endl;
	    success = false;
	}
	else
	{
	    width = loadedSurface->w;
	    height = loadedSurface->h;
	}

	SDL_FreeSurface(loadedSurface);
    }

    return success;
}

void Texture::render(sdlw::RendererShPtr renderer, SDL_Rect* clip, const int &xPos, const int &yPos)
{
    assert(renderer);

    SDL_Rect renderArea {xPos, yPos, width, height};

    if (clip != nullptr)
    {
	renderArea.w = clip->w;
	renderArea.h = clip->h;
    }

    SDL_RenderCopy(renderer.get(), texture.get(), clip, &renderArea);
}

const int& Texture::getWidth() const
{
    return width;
}

const int& Texture::getHeight() const
{
    return height;
}

const int& Texture::getXPos() const
{
    return xPos;
}

const int& Texture::getYPos() const
{
    return yPos;
}
