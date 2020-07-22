#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"
#include "sprite.hpp"

class Player : public Entity
{
public:
    Player(Sprite::SpriteShPtr spritePtr) : Entity(spritePtr) {};
    virtual void animate();
};

#endif
