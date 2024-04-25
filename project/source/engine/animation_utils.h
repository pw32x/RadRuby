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
void AnimationUtils_updateBatchedAnimation(struct game_object* gameObject);
void AnimationUtils_updateMetaSpriteAnimation(struct game_object* gameObject);
u8 AnimationUtils_updateBatchedAnimation_noLoop(struct game_object* gameObject);
u8 AnimationUtils_updatePlaneAnimation(struct game_object* gameObject);
u8 AnimationUtils_updateTileAnimation(struct game_object* gameObject);

// load 
u16 Load_BatchedAnimationResource(const Resource* resource);
u16 Load_MetaSpriteBatchedAnimationResource(const Resource* resource);
u16 Load_StreamedBatchedAnimationResource(const Resource* resource);
u16 Load_PlaneAnimationResource(const Resource* resource);
u16 Load_TileAnimationResource(const Resource* resource);

// setup
u16 Setup_BatchedAnimationResource(struct game_object* gameObject, const Resource* resource);
u16 Setup_MetaSpriteAnimationResource(struct game_object* gameObject, const Resource* resource);
u16 Setup_PlaneAnimationResource(struct game_object* gameObject, const Resource* resource);
u16 Setup_TileAnimationResource(struct game_object* gameObject, const Resource* resource);

// streaming

void AnimationUtils_UpdateStreamedBatchedAnimationFrame(struct game_object* gameObject);

// misc

void AnimationUtils_setBatchedAnimationFrame(struct game_object* gameObject, u8 animationFrameIndex);
void AnimationUtils_setMetaSpriteAnimationFrame(struct game_object* gameObject, u8 animationFrameIndex);

#endif