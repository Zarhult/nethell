#include "texture.hpp"
#include "sdlw.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <memory>
#include <assert.h>

void Texture::loadFromFile(const std::string &path)
{
    assert(texRenderer);

    // Reset if existing texture
    if (mTexture)
    {
        mTexture.reset();
        mWidth = 0;
        mHeight = 0;
    }

    SDL_Surface* loadedSurface {IMG_Load(path.c_str())};
    if (loadedSurface == nullptr)
    {
        std::string err {IMG_GetError()};
        throw std::runtime_error("Texture::loadFromFile error: " + err);
    }

    mTexture.reset(SDL_CreateTextureFromSurface(texRenderer.get(), loadedSurface));
    if (mTexture == nullptr)
    {
        std::string err {IMG_GetError()};
        throw std::runtime_error("Texture::loadFromFile error: " + err);
    }

    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);
}

void Texture::loadFromRenderedText(const std::string &text, TTF_Font* textFont, SDL_Color textColor)
{
    assert(texRenderer);

    // Reset if existing texture
    if (mTexture)
    {
        mTexture.reset();
        mWidth = 0;
        mHeight = 0;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(textFont, text.c_str(), textColor);
    if (textSurface == nullptr)
    {
        std::string err {TTF_GetError()};
        throw std::runtime_error("Texture::loadFromRenderedText error: " + err);
    }

    mTexture.reset(SDL_CreateTextureFromSurface(texRenderer.get(), textSurface));
    if (mTexture == nullptr)
    {
        std::string err {SDL_GetError()};
        throw std::runtime_error("Texture::loadFromRenderedText error: " + err);
    }

    mWidth = textSurface->w;
    mHeight = textSurface->h;

    SDL_FreeSurface(textSurface);
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
    return mWidth;
}

int Texture::getHeight() const
{
    return mHeight;
}

