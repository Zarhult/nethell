#include "player.hpp"
#include "spriteenums.hpp"

void Player::animate()
{
    if (mState == ENTITY_WALKING)
    {
        if (mSpritePtr->getSpriteNum() == PLAYER_WALK)
        {
            mSpritePtr->setSpriteNum(PLAYER_IDLE);
        }
        else
        {
            mSpritePtr->setSpriteNum(PLAYER_WALK);
        }
    }
}
