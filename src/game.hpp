#ifndef GAME_HPP
#define GAME_HPP

#include "spritesheet.hpp"
#include "spriteenums.hpp"
#include "entity.hpp"
#include "sdlw.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <vector>
#include <memory>

class Game
{
public:
    Game(); // Constructor initializes and loads everything needed for the game to run
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    
    /* Game Functions */
    
    // Sprite sheets contain each frame of an animation for a single entity, or a sheet of various static sprites, but never a
    // combination.
    void eventHandle(SDL_Event event); // Process an event
    void step(double timeStep); // Step game logic forward by timeStep milliseconds, incrementing step number
    void render(); // Render all onscreen sprites
    void loadSpriteSheet(const std::string &path, bool isAnimation, int spriteWidth, int spriteHeight, int spritesX,
                         int spritesY);
    void newEntity(SpriteName name, int startingSprite); // Create a new entity with given sprite (added to entity vector)
    
    /* Accessors */
    
    Entity::EntityShPtr getEntity(int entityVecPos) const;
    int getFrameStepCap() const;
    double getTimeStep() const;
    bool debugEnabled() const;
    bool isRunning() const;

private:
    /* Smart pointers used for things that have to survive end of a
       function call like loadSpriteSheet, and/or SDL smart pointer wrappers */
    sdlw::WindowShPtr mWindow {nullptr};
    sdlw::RendererShPtr mRenderer {nullptr};
    std::vector<SpriteSheet::SpriteSheetShPtr> mSpriteSheetVec;
    std::vector<Entity::EntityShPtr> mEntityVec;
    sdlw::FontShPtr mGameFont;

    /* Other SDL items */
    const Uint8 *mKeyboardState {SDL_GetKeyboardState(nullptr)};

    /* Game internals for timing, running, window size, framerate, etc. */
    const int mWinWidth {1920};
    const int mWinHeight {1080};
    const int mMaxFPS {144};
    const int mFrameStepCap {12}; // Max steps per frame (ideally always 1 step, but sometimes must skip frames for lag)
    const int mMinFPS {mMaxFPS / mFrameStepCap}; // FPS when skipping mFrameStepCap every frame
    const double mTimeStep {1000.0 / mMaxFPS}; // Time per step in ms
    
    double mGameLogicTime {0.0}; // Time of the game's internal logic - the result of time steps
    double mLastAnimTime {0}; // Last time sprites were animated
    bool mDebug {true}; // Whether or not to output game state information
    bool mIsRunning {false};
};

#endif
