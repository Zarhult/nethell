#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.hpp"

Texture::~Texture()
{
    this->free();
}

bool Texture::loadFromFile(SDL_Renderer* renderer, std::string path)
{
    // Free in case existing texture
    free();

    bool success { true };

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

void Texture::render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}

int Texture::getWidth()
{
    return width;
}

int Texture::getHeight()
{
    return height;
}

