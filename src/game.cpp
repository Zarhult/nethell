#include "game.hpp"
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
    mGameFont.reset(TTF_OpenFont("/usr/share/fonts/liberation/LiberationSans-Regular.ttf", 16));
    if (mGameFont == nullptr)
    {
        throw std::runtime_error(TTF_GetError());
    }

    // Populate mSpriteSheetVec
    this->loadSpriteSheet("sprites/wizard.png", true, 120, 120, 2, 1);

    // Set up starting entities
    this->newEntity(PLAYER, PLAYER_IDLE);
    this->getEntity(PLAYER)->toggleSprite(); // Default position is (0, 0), so no need to set it

    // If all initialized successfully...
    mIsRunning = true;
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
    // does this need to be a while (SDL_PollEvent(&mEvent) != 0) ?
    SDL_PollEvent(&mEvent);
    
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

    // Get keyboard state to handle key events
    const Uint8* keyboardState {SDL_GetKeyboardState(NULL)};

    Entity::EntityShPtr player = mEntityVec.at(PLAYER);
    // Animate player movement
    if (keyboardState[SDL_SCANCODE_W] || keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_S] || keyboardState[SDL_SCANCODE_D])
    {
        if (this->isNthFrame(36))
        {
            if (player->getSpriteNum() == PLAYER_WALK)
            {
                player->changeSprite(PLAYER_IDLE);
            }
            else
            {
                player->changeSprite(PLAYER_WALK);
            }
        }
    }
    else
    {
        player->changeSprite(PLAYER_IDLE);
    }
    
    // Move player
    if (keyboardState[SDL_SCANCODE_W])
    {
        player->shiftSprite(0, -5);
    }
    else if (keyboardState[SDL_SCANCODE_A])
    {
        player->shiftSprite(-5, 0);
        player->setSpriteFlipType(SDL_FLIP_HORIZONTAL);
    }
    else if (keyboardState[SDL_SCANCODE_S])
    {
        player->shiftSprite(0, 5);
    }
    else if (keyboardState[SDL_SCANCODE_D])
    {
        player->shiftSprite(5, 0);
        player->setSpriteFlipType(SDL_FLIP_NONE);
    }
    
    /*
    if (mEvent.type == SDL_KEYDOWN)
    {
        SDL_Keycode keycode = mEvent.key.keysym.sym;
        if (keycode == SDLK_w || keycode == SDLK_a || keycode == SDLK_s || keycode == SDLK_d)
        {
            if (this->isNthFrame(36))
            {
                if (mEntityVec.at(0)->getSpriteNum() == PLAYER_WALK)
                {
                    mEntityVec.at(0)->changeSprite(PLAYER_IDLE);
                }
                else
                {
                    mEntityVec.at(0)->changeSprite(PLAYER_WALK);
                }
            }
            
            switch(mEvent.key.keysym.sym)
            {
            case SDLK_w:
                mEntityVec.at(PLAYER)->shiftSprite(0, -10);
                break;

            case SDLK_a:
                mEntityVec.at(PLAYER)->shiftSprite(-10, 0);
                break;

            case SDLK_s:
                mEntityVec.at(PLAYER)->shiftSprite(0, 10);
                break;

            case SDLK_d:
                mEntityVec.at(PLAYER)->shiftSprite(10, 0);
                break;

            default:
                break;

            }
        }
    }
    */
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

void Game::setNextFrame(Uint32 val)
{
    mNextFrame = val;
}

Entity::EntityShPtr Game::getEntity(int entityVecPos) const
{
    return mEntityVec.at(entityVecPos);
}

bool Game::isRunning() const
{
    return mIsRunning;
}

Uint32 Game::getFrameStep() const
{
    return mFrameStep;
}

Uint32 Game::getNextFrame() const
{
    return mNextFrame;
}

bool Game::isNthFrame(int n) const
{
    return (((mNextFrame / mFrameStep) % n) == 0);
}
