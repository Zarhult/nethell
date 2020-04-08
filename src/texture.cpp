#include "texture.hpp"
#include "sdlw.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <memory>
#include <assert.h>

Texture::Texture(sdlw::RendererShPtr renderer)
{
    assert(renderer);

    this->texRenderer = renderer;
}

bool Texture::loadFromFile(const std::string &path)
{
    assert(texRenderer);

    // Reset if existing texture
    if (mTexture)
    {
	mTexture.reset();
	mWidth = 0;
	mHeight = 0;
    }

    bool success {true};

    SDL_Surface* loadedSurface {IMG_Load(path.c_str())};
    if (loadedSurface == nullptr)
    {
	std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
	success = false;
    }
    else
    {
	mTexture.reset(SDL_CreateTextureFromSurface(texRenderer.get(), loadedSurface));
	if (mTexture == nullptr)
	{
	    std::cerr << "SDL_CreateTextureFromSurface error: " << SDL_GetError() << std::endl;
	    success = false;
	}
	else
	{
	    mWidth = loadedSurface->w;
	    mHeight = loadedSurface->h;
	}

	SDL_FreeSurface(loadedSurface);
    }

    return success;
}

bool Texture::loadFromRenderedText(const std::string &text, TTF_Font* textFont, SDL_Color textColor)
{
    assert(texRenderer);

    // Reset if existing texture
    if (mTexture)
    {
	mTexture.reset();
	mWidth = 0;
	mHeight = 0;
    }

    bool success {true};

    SDL_Surface* textSurface = TTF_RenderText_Solid(textFont, text.c_str(), textColor);
    if (textSurface == nullptr)
    {
	std::cerr <<  "TTF_RenderText_Solid error: " << TTF_GetError() << std::endl;
	success = false;
    }
    else
    {
	mTexture.reset(SDL_CreateTextureFromSurface(texRenderer.get(), textSurface));
	if (mTexture == nullptr)
	{
	    std::cerr << "SDL_CreateTextureFromSurface error: " << SDL_GetError() << std::endl;
	    success = false;
	}
	else
	{
	    mWidth = textSurface->w;
	    mHeight = textSurface->h;
	}

	SDL_FreeSurface(textSurface);
    }

    return success;
}

void Texture::render(int xPos, int yPos, SDL_Rect* clip)
{
    assert(texRenderer);

    SDL_Rect renderArea {xPos, yPos, mWidth, mHeight};

    if (clip != nullptr)
    {
	renderArea.w = clip->w;
	renderArea.h = clip->h;
    }

    SDL_RenderCopy(texRenderer.get(), mTexture.get(), clip, &renderArea);
}

int Texture::getWidth() const
{
    assert(this);

    return mWidth;
}

int Texture::getHeight() const
{
    assert(this);

    return mHeight;
}

