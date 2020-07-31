#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "sprite.hpp"
#include <memory>

// Internal states used so functions like animate() can set the sprite appropriately without
// the caller needing to do anything besides possibly set the state
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
    Entity(Sprite::SpriteShPtr spritePtr, double speed, int maxHP, int HP) : mSpritePtr(spritePtr), mSpeed(speed), mMaxHP(maxHP), mHP(HP) {};
    virtual void animate() = 0; // Progress animation depending on the entity's state
    void setState(EntityState state);

    Sprite::SpriteShPtr getSprite() const;
    EntityState getState() const;
    double getSpeed() const;
    int getMaxHP() const;
    int getHP() const;
    
protected:
    Sprite::SpriteShPtr mSpritePtr {nullptr}; // Pointer to entity's sprite
    EntityState mState {ENTITY_IDLE};
    double mSpeed; // Movement speed in pixels per ms
    int mMaxHP; // Add stats here...
    int mHP {};
};

#endif

// there is no entity without 4 corners
