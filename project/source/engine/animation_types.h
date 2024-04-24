#ifndef ANIMATION_TYPES_INCLUDE_H
#define ANIMATION_TYPES_INCLUDE_H

#include <genesis.h>
#include "engine\vdptypes.h"
#include "engine\resource_types.h"

typedef struct
{
    s16 xoffset;
    s16 yoffset;
	s16 xFlippedOffset;
    u16 tileAttribute;
    u16 sgdkSpriteSize;
} GGSprite;

typedef struct Frame
{
    const GGSprite* const* sprites;
    u8 numSprites; // no more than 255 sprites
	u8 frameTriggerDataOffset; // only 255 entries for trigger data
    u16 frameDelayTime;
    const struct Frame* nextFrame;
} GGFrame;

typedef struct
{
    u8 resourceType;
    const GGFrame* const* frames;	    // pointer to animation frames
    u16 numberOfFrames;				// number of frames
    u16 width;						// width of the total area of the sprite in pixels
    u16 height;						// height of the total area of the sprite in pixels
    u16 maxNumberOfTilesPerFrame;	// the number of tiles required to store one frame
    u16 totalTiles;					// the total number of tiles in the animation
	//u16 totalAnimationTime;			// the total time duration of the animation
    const u32 const* allSpriteData;		// start of the sprite data
	const s16 const* frameTriggerData;	// data that might be attached to a frame
} GGAnimation;

typedef void (*drawPlaneAnimationFrameFunctionType)(u16 plan, u16 x, u16 y, u16 tileIndex);

typedef struct GGPlaneAnimationFrame
{
	drawPlaneAnimationFrameFunctionType drawFrame;	
	u16 frameDelayTime;
	const struct PlaneAnimationFrame* nextFrame;
} GGPlaneAnimationFrame;

typedef struct
{
    const GGPlaneAnimationFrame* const* frames;	// pointer to animation frames
    u16 numberOfFrames;							// number of frames
    u16 tileWidth;								// width of the total area of the frame in tiles
    u16 tileHeight;								// height of the total area of the frame in tiles
    u16 totalTiles;								// the total number of tiles in the animation
    u32 const* tileData;						// start of the tile data
} GGPlaneAnimation;

#define DIRECTION_LEFT  1
#define DIRECTION_RIGHT 0

#endif
