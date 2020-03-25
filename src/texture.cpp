#include <iostream>
#include <memory>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.hpp"

Texture::Texture(sdlw::RendererShPtr renderer)
{
    assert(renderer);

    this->texRenderer = renderer;
}

bool Texture::loadFromFile(const std::string &path)
{
    assert(texRenderer);

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
	texture.reset(SDL_CreateTextureFromSurface(texRenderer.get(), loadedSurface));
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

void Texture::render(int xPos, int yPos, SDL_Rect* clip)
{
    assert(texRenderer);

    SDL_Rect renderArea {xPos, yPos, width, height};

    if (clip != nullptr)
    {
	renderArea.w = clip->w;
	renderArea.h = clip->h;
    }

    SDL_RenderCopy(texRenderer.get(), texture.get(), clip, &renderArea);
}

int Texture::getWidth() const
{
    return width;
}

int Texture::getHeight() const
{
    return height;
}

