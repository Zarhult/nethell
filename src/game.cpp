#include "game.hpp"
#include "player.hpp"
#include "spriteenums.hpp"
#include "texture.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <assert.h>
#include <vector>
#include <memory>

Game::Game(int winWidth, int winHeight)
{
    // Initialize SDL and prepare the window and renderer, with vsync
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        throw std::runtime_error(SDL_GetError());
    }

    mWindow.reset(SDL_CreateWindow("Nethell", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight,
                                   SDL_WINDOW_SHOWN));
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
    mGameFont.reset(TTF_OpenFont("/usr/share/fonts/liberation/LiberationSans-Regular.ttf", 16));
    if (mGameFont == nullptr)
    {
        throw std::runtime_error(TTF_GetError());
    }

    // Populate mSpriteSheetVec
    this->loadSpriteSheet("sprites/wizard.png", true, 120, 120, 2, 1);

    // Set up starting entities
    this->newEntity(PLAYER, PLAYER_IDLE);
    this->getEntity(PLAYER)->getSprite()->toggleOnscreen(); // Default position is (0, 0), so no need to set it

    // If all initialized successfully...
    mIsRunning = true;
}

void Game::loadSpriteSheet(const std::string &path, bool isAnimation, int spriteWidth, int spriteHeight, int spritesX,
                           int spritesY)
{
    SpriteSheet::SpriteSheetShPtr spriteSheet {std::make_shared<SpriteSheet>(mRenderer, isAnimation, spriteWidth, spriteHeight, 
                                                                             spritesX, spritesY)};
    spriteSheet->loadFromFile(path);
    mSpriteSheetVec.push_back(std::move(spriteSheet));
}

void Game::eventHandle()
{
    while(SDL_PollEvent(&mEvent))
    {
        if (mEvent.type == SDL_QUIT)
        {
            mIsRunning = false;
        }
        
        if (mEvent.type == SDL_MOUSEBUTTONDOWN)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            // stuff with mouse...
        }
    }
}

void Game::step()
{
    // Progress all sprite animations once every 15 frames (0.25 s)
    // Note that doing this with a number like 31 (doesn't evenly divide FPS) would not animate every 31 frames
    for (unsigned i = 0; i < mEntityVec.size(); ++i)
    {
        if (mFrame % 1 == 0)
        {
            mEntityVec.at(i)->animate();
        }
    }

    // If player is moving...
    if (mKeyboardState[SDL_SCANCODE_W] || mKeyboardState[SDL_SCANCODE_A] || mKeyboardState[SDL_SCANCODE_S] ||
        mKeyboardState[SDL_SCANCODE_D])
    {
        mEntityVec.at(PLAYER)->setState(ENTITY_WALKING);

        Sprite::SpriteShPtr playerSprite = mEntityVec.at(PLAYER)->getSprite();
        if (mKeyboardState[SDL_SCANCODE_W])
        {
            playerSprite->shiftXY(0, -10);
            std::cout << mFrame << std::endl;
        }
        else if (mKeyboardState[SDL_SCANCODE_A])
        {
            playerSprite->shiftXY(-10, 0);
            playerSprite->setFlipType(SDL_FLIP_HORIZONTAL);
        }
        else if (mKeyboardState[SDL_SCANCODE_S])
        {
            playerSprite->shiftXY(0, 10);
        }
        else if (mKeyboardState[SDL_SCANCODE_D])
        {
            playerSprite->shiftXY(10, 0);
            playerSprite->setFlipType(SDL_FLIP_NONE);
        }
    }
    else
    {
        mEntityVec.at(PLAYER)->setState(ENTITY_IDLE);
    }
    
    // Update frame number
    mFrame = (mFrame % mFPS) + 1;
}

void Game::render()
{
    SDL_RenderClear(mRenderer.get());

    // Render all onscreen sprites
    for (unsigned i = 0; i < mEntityVec.size(); ++i)
    {
        if (mEntityVec.at(i)->getSprite()->isOnscreen())
        {
            mEntityVec.at(i)->getSprite()->render();
        }
    }

    SDL_RenderPresent(mRenderer.get());
}

void Game::newEntity(SpriteName name, int startingSprite)
{
    if (mSpriteSheetVec.at(name)->isAnimation() == true) {
        Sprite::SpriteShPtr sprite {std::make_shared<Sprite>(mSpriteSheetVec.at(name), startingSprite)};
        Entity::EntityShPtr entity {nullptr};
        
        switch(name)
        {
        case PLAYER:
            entity = std::make_shared<Player>(sprite);
            break;
            
        default:
            throw std::logic_error("Attempted to create an entity without a valid sprite enum.");
            break;
        }

        mEntityVec.push_back(std::move(entity));
    } else {
        throw std::logic_error("Attempted to create entity from unanimated sprite sheet");
    }
}

Entity::EntityShPtr Game::getEntity(int entityVecPos) const
{
    return mEntityVec.at(entityVecPos);
}

bool Game::isRunning() const
{
    return mIsRunning;
}

int Game::getTimeStep() const
{
    return 1000 / mFPS;
}

int Game::getFrame() const
{
    return mFrame;
}
