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
    Game(int winWidth, int winHeight); // Constructor initializes and loads everything needed for the game to run
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    
    /* Game Functions */
    
    // Sprite sheets contain each frame of an animation for a single entity, or a sheet of various static sprites, but never a
    // combination.
    void eventHandle(); // Process an event
    void step(); // Step non-event game logic forward, incrementing frame number
    void render(); // Render all onscreen sprites
    void loadSpriteSheet(const std::string &path, bool isAnimation, int spriteWidth, int spriteHeight, int spritesX,
                         int spritesY);
    void newEntity(SpriteName name, int startingSprite); // Create a new entity with given sprite (added to entity vector)
    
    /* Accessors */
    
    Entity::EntityShPtr getEntity(int entityVecPos) const;
    bool isRunning() const;
    int getTimeStep() const; // Returns time per frame in ms
    int getFrame() const;
    
private:
    // Smart pointers used for things that have to survive end of a function call like loadSpriteSheet
    sdlw::WindowShPtr mWindow {nullptr};
    sdlw::RendererShPtr mRenderer {nullptr};
    std::vector<SpriteSheet::SpriteSheetShPtr> mSpriteSheetVec;
    std::vector<Entity::EntityShPtr> mEntityVec;
    sdlw::FontShPtr mGameFont;
    SDL_Event mEvent;
    const int mFPS {60}; // Max FPS game will attempt to render
    int mFrame {0}; // Current frame out of one second interval
    
    bool mIsRunning {false};
};

#endif
