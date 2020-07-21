#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "sprite.hpp"
#include <memory>

class Entity
{
public:
    using EntityShPtr = std::shared_ptr<Entity>;
    
public:
    Entity(Sprite::SpriteShPtr spritePtr) : mSpritePtr(spritePtr) {};
    
    void render();
    void moveSprite(int xPos, int yPos); // Set the sprite's x and y positions
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
