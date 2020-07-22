#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "sprite.hpp"
#include <memory>

//TODO: don't use redundant functions, have a function that returns the sprite pointer and use the sprite functions directly
// fix this anywhere else it's done

class Entity
{
public:
    using EntityShPtr = std::shared_ptr<Entity>;
    
public:
    Entity(Sprite::SpriteShPtr spritePtr) : mSpritePtr(spritePtr) {};
    
    void render();
    void shiftSprite(int xPos, int yPos); // Adjust the sprite's x and y positions
    void setSpriteAngle(double angle);
    void setSpriteFlipType(SDL_RendererFlip flipType);
    void changeSprite(int newSpriteNum); /* Change entity's sprite number with respect to its sprite sheet 
                                            (useful for rendering animations) */
    void toggleSprite(); // Toggle sprite visibility
    
    int getSpriteNum()  const;
    int getSpriteXPos() const;
    int getSpriteYPos() const;
    int isOnscreen()    const;
    int getMaxHP()      const;
    int getHP()         const;
    
private:
    Sprite::SpriteShPtr mSpritePtr {nullptr}; // Pointer to entity's sprite
    int maxHP; // Add stats here...
    int HP;
};

#endif
