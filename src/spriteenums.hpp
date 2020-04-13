/* Sprite Enums set up to work with a particular loading order of sprite sheets in main */

#ifndef SPRITEENUMS_HPP
#define SPRITEENUMS_HPP

// First comes all animated sprites, followed by an enum for each sheet of static sprites. Static sprites can easily be set to any sprite in
//	their respective sprite sheet with the changeSprite function.
// Matches order of sprites in sprite sheet, starting from 0.
enum SpriteName
{
    PLAYER
};

// The rest of the enumerations define the frames of a sprite's animation(s) or the elements of a static sprite sheet, 0 being the first 
//	sprite of its sprite sheet, 1 the next, etc.
// Should only be used as the second argument in the changeSprite function.
enum SpritePlayerFrames
{
    PLAYER_IDLE,
    PLAYER_WALK
};

#endif

