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

Game::Game()
{
    // Initialize SDL and prepare the window and renderer
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        throw std::runtime_error(SDL_GetError());
    }

    mWindow.reset(SDL_CreateWindow("Nethell", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWinWidth, mWinHeight,
                                   SDL_WINDOW_SHOWN));
    if (mWindow == nullptr) 
    {
        throw std::runtime_error(SDL_GetError());
    }
    // Fullscreen window
    SDL_SetWindowFullscreen(mWindow.get(), SDL_WINDOW_FULLSCREEN);

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
    mGameFont.reset(TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 16));
    if (mGameFont == nullptr)
    {
        throw std::runtime_error(TTF_GetError());
    }

    // Populate mSpriteSheetVec
    this->loadSpriteSheet("sprites/wizard.png", true, 120, 120, 2, 1);

    // Set up starting entities, in the order specified in spriteenums.hpp
    // TODO: make this automatically loop through the enums, with starting sprite of 0
    this->newEntity(PLAYER, PLAYER_IDLE);
    this->getEntity(PLAYER)->getSprite()->toggleOnscreen(); // Default position is (0, 0), so no need to set it

    // If all initialized successfully...
    mIsRunning = true;
    mRenderReady = true;
}

void Game::eventHandle(SDL_Event event)
{
    if (event.type == SDL_QUIT)
    {
        mIsRunning = false;
    }
    
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        // stuff with mouse...
    }
}

void Game::step(double timeStep)
{
    // Progress all sprite animations once every 0.25 s
    if (mGameLogicTime - mLastAnimTime >= 250) {
        mLastAnimTime = mGameLogicTime;
        for (unsigned i = 0; i < mEntityVec.size(); ++i)
        {
            mEntityVec.at(i)->animate();
        }
    }

    // for testing purposes
    if (mKeyboardState[SDL_SCANCODE_Q]) {
        mIsRunning = false;
    }
    
    // If player is moving...
    if (mKeyboardState[SDL_SCANCODE_W] || mKeyboardState[SDL_SCANCODE_A] || mKeyboardState[SDL_SCANCODE_S] ||
        mKeyboardState[SDL_SCANCODE_D])
    {
        mEntityVec.at(PLAYER)->setState(ENTITY_WALKING);

        Sprite::SpriteShPtr playerSprite = mEntityVec.at(PLAYER)->getSprite();
        double speed = mEntityVec.at(PLAYER)->getSpeed();

        // perhaps should use switch on keysym events instead of key states for stuff like this
        if (mKeyboardState[SDL_SCANCODE_W])
        {
            playerSprite->shiftXY(0.0, -speed * timeStep);
        }
        else if (mKeyboardState[SDL_SCANCODE_A])
        {
            playerSprite->shiftXY(-speed * timeStep, 0.0);
            playerSprite->setFlipType(SDL_FLIP_HORIZONTAL);
        }
        else if (mKeyboardState[SDL_SCANCODE_S])
        {
            playerSprite->shiftXY(0.0, speed * timeStep);
        }
        else if (mKeyboardState[SDL_SCANCODE_D])
        {
            playerSprite->shiftXY(speed * timeStep, 0.0);
            playerSprite->setFlipType(SDL_FLIP_NONE);
        }
    }
    else
    {
        mEntityVec.at(PLAYER)->setState(ENTITY_IDLE);
    }

    // Update game's internal clock
    mGameLogicTime += timeStep;

    // Signal that a render would not be a waste of time (state has changed)
    mRenderReady = true;
}

void Game::render()
{
    if (mRenderReady)
    {
        if (mDebug)
        {
            std::cout << "Rendering." << std::endl;
        }

        SDL_RenderClear(mRenderer.get());

        // Render all onscreen sprites
        for (unsigned i = 0; i < mEntityVec.size(); ++i)
        {
            if (mEntityVec.at(i)->getSprite()->isOnscreen())
            {
                mEntityVec.at(i)->getSprite()->render();
            }
        }

        mRenderReady = false;
    }
    SDL_RenderPresent(mRenderer.get());
}

void Game::loadSpriteSheet(const std::string &path, bool isAnimation, int spriteWidth, int spriteHeight, int spritesX,
                           int spritesY)
{
    SpriteSheet::SpriteSheetShPtr spriteSheet {std::make_shared<SpriteSheet>(mRenderer, isAnimation, spriteWidth, spriteHeight, 
                                                                             spritesX, spritesY)};
    spriteSheet->loadFromFile(path);
    mSpriteSheetVec.push_back(std::move(spriteSheet));
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

int Game::getFrameStepCap() const
{
    return mFrameStepCap;
}

double Game::getTimeStep() const
{
    return mTimeStep;
}

bool Game::debugEnabled() const
{
    return mDebug;
}
bool Game::isRunning() const
{
    return mIsRunning;
}
