/* Sprite Enums set up to work with a particular loading order of sprite sheets in main */

#ifndef SPRITEENUMS_HPP
#define SPRITEENUMS_HPP

// First comes each animated sprite sheet, followed by each sheet of static sprites.
// Matches order that each sprite sheet is loaded in main.
enum SpriteName
{
    PLAYER
};

// The rest of the enumerations define the frames of a sprite's animation(s) or the elements of a static sprite sheet, 0 being the first 
// sprite of its sprite sheet, 1 the next, etc. The enums are defined in the same order as the sprite sheets above.
enum SpritePlayerFrames
{
    PLAYER_IDLE,
    PLAYER_WALK
};

#endif
