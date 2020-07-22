#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "sprite.hpp"
#include <memory>

enum EntityState
{
    ENTITY_IDLE,
    ENTITY_WALKING
};
    
class Entity
{
public:
    using EntityShPtr = std::shared_ptr<Entity>;
    
public:
    Entity(Sprite::SpriteShPtr spritePtr) : mSpritePtr(spritePtr) {};
    virtual void animate() = 0; // Progress animation depending on the entity's state
    void setState(EntityState state);

    Sprite::SpriteShPtr getSprite() const;
    int getMaxHP() const;
    int getHP()    const;
    
protected:
    Sprite::SpriteShPtr mSpritePtr {nullptr}; // Pointer to entity's sprite
    EntityState mState {ENTITY_IDLE};
    int maxHP; // Add stats here...
    int HP;
};

#endif

// there is no entity without 4 corners
