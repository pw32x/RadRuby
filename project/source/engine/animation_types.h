#ifndef ANIMATION_TYPES_INCLUDE_H
#define ANIMATION_TYPES_INCLUDE_H

#include <genesis.h>
#include "engine\vdp_types.h"
#include "engine\resource_types.h"

struct game_object;

typedef struct
{
    void (*Draw)(struct game_object* gameObject);
    void (*UpdateAnimation)(struct game_object* gameObject);
    const void* startingAnimationFrame;
    u8 startAnimationFrameIndex;
    u8 animationTime;
} Ruby_AnimationSetup;

typedef struct
{
    s16 xoffset;
    s16 yoffset;
	s16 xFlippedOffset;
    u16 tileAttribute;
    u16 sgdkSpriteSize;
} Ruby_Sprite;

typedef struct ruby_frame
{
    const Ruby_Sprite* const* sprites;
    u8 numSprites; // no more than 255 sprites
	u8 frameTriggerDataOffset; // only 255 entries for trigger data
    u16 frameTime;
    const struct ruby_frame* nextFrame;
} Ruby_Frame;

typedef struct
{
    u8 resourceType;
    const Ruby_AnimationSetup* animationSetup;
    const Ruby_Frame* const* frames;	// pointer to animation frames
    u16 numFrames;				        // number of frames
    u16 width;						    // width of the total area of the sprite in pixels
    u16 height;						    // height of the total area of the sprite in pixels
    u16 maxNumberOfTilesPerFrame;	    // the number of tiles required to store one frame
    u16 numTotalTiles;					// the total number of tiles in the animation
    const u32 const* tileData;		    // start of the sprite tile data
	const s16 const* frameTriggerData;	// data that might be attached to a frame
    u16* vdpLocation;
} Ruby_Animation;

typedef void (*drawPlaneAnimationFrameFunctionType)(u16 plan, u16 x, u16 y, u16 tileIndex);

typedef struct ruby_planeanimationframe
{
	drawPlaneAnimationFrameFunctionType drawFrame;
	u16 frameTime;
	const struct ruby_planeanimationframe* nextFrame;
} Ruby_PlaneAnimationFrame;

typedef struct
{
    const Ruby_PlaneAnimationFrame* const* frames;	// pointer to animation frames
    u16 numFrames;							    // number of frames
    u16 tileWidth;								    // width of the total area of the frame in tiles
    u16 tileHeight;								    // height of the total area of the frame in tiles
    u16 numTotalTiles;								    // the total number of tiles in the animation
    u32 const* tileData;						    // start of the tile data
} Ruby_PlaneAnimation;

#define DIRECTION_LEFT  1
#define DIRECTION_RIGHT 0

#endif
