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
        Game(int winWidth, int winHeight);
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;

        /* Game Functions */

        // Sprite sheets contain each frame of an animation for a single entity, or a
        // sheet of various static sprites, but never a combination.
        void loadSpriteSheet(const std::string &path, bool isAnimation, int spriteWidth, int spriteHeight, int spritesX, int spritesY);
        void eventHandle(); // Process an event
        void render();      // Render all onscreen sprites
        void newEntity(SpriteName name, int startingSprite); // Create a new entity with given sprite (added to entity vector)

        /* Accessors */

        Entity::EntityShPtr getEntity(int entityVecPos) const;
        bool getRunStatus() const;

    private:
        sdlw::WindowShPtr mWindow {nullptr};
        sdlw::RendererShPtr mRenderer {nullptr};
        std::vector<SpriteSheet::SpriteSheetShPtr> mSpriteSheetVec;
        std::vector<Entity::EntityShPtr> mEntityVec;
        sdlw::FontShPtr mGameFont;
        SDL_Event mEvent;

        bool mIsRunning {false};
};

#endif
