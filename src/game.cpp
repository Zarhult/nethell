#include "game.hpp"
#include "spriteenums.hpp"
#include "texture.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <vector>
#include <memory>
#include <assert.h>

Game::Game(int winWidth, int winHeight)
{
    // Initialize SDL and prepare the window and renderer
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        throw std::runtime_error(SDL_GetError());
    }

    mWindow.reset(SDL_CreateWindow("Nethell", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight, SDL_WINDOW_SHOWN));
    if (mWindow == nullptr) 
    {
        throw std::runtime_error(SDL_GetError());
    } 

    mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    if (mRenderer == nullptr)
    {
        throw std::runtime_error(SDL_GetError());
    }
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

    // Set game font    
    mGameFont = TTF_OpenFont("/usr/share/fonts/liberation/LiberationSans-Regular.ttf", 16);
    if (mGameFont == nullptr)
    {
        throw std::runtime_error(TTF_GetError());
    }

    // If all initialized successfully...
    mIsRunning = true;
}

Game::~Game()
{
    TTF_CloseFont(mGameFont);
}

void Game::loadSpriteSheet(const std::string &path, bool isAnimation, int spriteWidth, int spriteHeight, int spritesX, int spritesY)
{
    SpriteSheet::SpriteSheetShPtr spriteSheet {std::make_shared<SpriteSheet>(mRenderer, isAnimation, spriteWidth, spriteHeight, 
                                                                             spritesX, spritesY)};
    spriteSheet->loadFromFile(path);
    mSpriteSheetVec.push_back(std::move(spriteSheet));
}

void Game::eventHandle()
{
    SDL_PollEvent(&mEvent);

    if (mEntityVec.at(PLAYER)->getSpriteNum() == PLAYER_WALK)
    {
        mEntityVec.at(PLAYER)->changeSprite(PLAYER_IDLE);
    }
    else
    {
        mEntityVec.at(PLAYER)->changeSprite(PLAYER_WALK);
    }

    if (mEvent.type == SDL_QUIT)
    {
        mIsRunning = false;
    }
}

void Game::render()
{
    SDL_RenderClear(mRenderer.get());

    for (unsigned i = 0; i < mEntityVec.size(); ++i)
    {
        assert(mEntityVec.at(i));

        if (mEntityVec.at(i)->isOnscreen())
        {
            mEntityVec.at(i)->render();
        }
    }

    SDL_RenderPresent(mRenderer.get());
}

void Game::newEntity(SpriteName name, int startingSprite)
{
    if (mSpriteSheetVec.at(name)->isAnimation() == true) {
        Sprite::SpriteShPtr sprite {std::make_shared<Sprite>(mSpriteSheetVec.at(name), startingSprite)};
        Entity::EntityShPtr entity {std::make_shared<Entity>(sprite)}; 

        mEntityVec.push_back(std::move(entity));
    } else {
        throw std::runtime_error("Attempted to create entity from unanimated sprite sheet");
    }
}

Entity::EntityShPtr Game::getEntity(int entityVecPos) const
{
    assert(this);

    return mEntityVec.at(entityVecPos);
}

bool Game::getRunStatus() const
{
    assert(this);

    return mIsRunning;
}

