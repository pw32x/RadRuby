#ifndef ANIMATION_UTILS_INCLUDE_H
#define ANIMATION_UTILS_INCLUDE_H

#include "genesis.h"
#include "engine/animation_types.h"
#include "engine/resource_types.h"

struct game_object;

#define ANIMATION_NO_CHANGE			0
#define ANIMATION_CHANGED_FRAME		1
#define ANIMATION_FINISHED			2


// update
void AnimationUtils_updateStandardAnimation(struct game_object* gameObject);
void AnimationUtils_updateStreamedAnimation(struct game_object* gameObject);
u8 AnimationUtils_updateStandardAnimation_noLoop(struct game_object* gameObject);
u8 AnimationUtils_updatePlaneAnimation(struct game_object* gameObject);
u8 AnimationUtils_updateTileAnimation(struct game_object* gameObject);

// load 
u16 Load_StandardAnimationResource(const Resource* resource);
u16 Load_StreamedAnimationResource(const Resource* resource);
u16 Load_PlaneAnimationResource(const Resource* resource);
u16 Load_TileAnimationResource(const Resource* resource);

// setup
u16 Setup_StandardAnimationResource(struct game_object* gameObject, const Resource* resource);
u16 Setup_StreamedAnimationResource(struct game_object* gameObject, const Resource* resource);
u16 Setup_PlaneAnimationResource(struct game_object* gameObject, const Resource* resource);
u16 Setup_TileAnimationResource(struct game_object* gameObject, const Resource* resource);

// streaming
void AnimationUtils_UpdateStreamedAnimationFrame(struct game_object* gameObject);

// misc
void AnimationUtils_setStandardAnimationFrame(struct game_object* gameObject, u8 animationFrameIndex);

#endif