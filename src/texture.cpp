#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.hpp"

Texture::~Texture()
{
    free();
}

bool Texture::loadFromFile(SDL_Renderer* renderer, const std::string &path)
{
    // Free in case existing texture
    free();

    bool success {true};

    SDL_Surface* loadedSurface { IMG_Load(path.c_str()) };
    if (loadedSurface == nullptr)
    {
	std::cout << "IMG_Load error: " << IMG_GetError() << std::endl;
	success = false;
    }
    else
    {
	texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (texture == nullptr)
	{
	    std::cout << "SDL_CreateTextureFromSurface error: " << SDL_GetError() << std::endl;
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

void Texture::free()
{
    if (texture != nullptr)
    {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	width = 0;
	height = 0;
    }
}

void Texture::render(SDL_Renderer* renderer, const int &x, const int &y)
{
    SDL_Rect renderArea {x, y, width, height};
    SDL_RenderCopy(renderer, texture, nullptr, &renderArea);
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
