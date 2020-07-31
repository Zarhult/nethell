#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"
#include "sprite.hpp"

class Player : public Entity
{
public:
    Player(Sprite::SpriteShPtr spritePtr) : Entity(spritePtr, 0.5, 10, 10) {};
    virtual void animate();
};

#endif
