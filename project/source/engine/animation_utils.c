#include "animation_utils.h"
#include "engine/base_defines.h"
#include "engine/object_types.h"
#include "engine/vdptile_manager.h"
#include "engine/draw_utils.h"
#include <string.h>

void AnimationUtils_updateStandardAnimation(GameObject* gameObject)
{
	if (!gameObject->animationTime)
	{
		gameObject->currentFrame = gameObject->currentFrame->nextFrame;
		gameObject->animationTime = gameObject->currentFrame->frameTime;
	}

	gameObject->animationTime--;
}

void AnimationUtils_updateStreamedAnimation(GameObject* gameObject)
{
	/*
	if (!gameObject->animationTime)
	{
		gameObject->currentMetaSpriteAnimationFrame = gameObject->currentMetaSpriteAnimationFrame->nextFrame;
		gameObject->animationTime = gameObject->currentMetaSpriteAnimationFrame->frameTime;
	}

	gameObject->animationTime--;
	*/
}

u8 AnimationUtils_updateStandardAnimation_noLoop(GameObject* gameObject)
{
	if (!gameObject->animationTime--)
	{
		gameObject->currentAnimationFrameIndex++;

		if (gameObject->currentAnimationFrameIndex == gameObject->animation->numFrames)
		{
			return ANIMATION_FINISHED;
		}

		gameObject->currentFrame = gameObject->animation->frames[gameObject->currentAnimationFrameIndex];
		gameObject->animationTime = gameObject->currentFrame->frameTime;
		return ANIMATION_CHANGED_FRAME;
	}

	return ANIMATION_NO_CHANGE;
}

// plane

u8 AnimationUtils_updatePlaneAnimation(GameObject* gameObject)
{
	/*
	if (!gameObject->animationTime--)
	{
		gameObject->currentPlaneAnimationFrame = gameObject->currentPlaneAnimationFrame->nextFrame;
		gameObject->animationTime = gameObject->currentPlaneAnimationFrame->frameTime;
		return ANIMATION_CHANGED_FRAME;
	}
	*/

	return ANIMATION_NO_CHANGE;
}

u8 AnimationUtils_updateTileAnimation(GameObject* gameObject)
{
	/*
	if (!gameObject->animationTime--)
	{
		gameObject->currentTileAnimationFrame = gameObject->currentTileAnimationFrame->nextFrame;
		gameObject->animationTime = gameObject->currentTileAnimationFrame->frameTime;
		return ANIMATION_CHANGED_FRAME;
	}
	*/

	return ANIMATION_NO_CHANGE;
}

void AnimationUtils_setStandardAnimationFrame(GameObject* gameObject, u8 animationFrameIndex)
{
	gameObject->currentAnimationFrameIndex = animationFrameIndex;
	gameObject->currentFrame = gameObject->animation->frames[animationFrameIndex]; 
	gameObject->animationTime = gameObject->currentFrame->frameTime;
}


u16 Load_StandardAnimationResource(const Resource* resource)
{
	const Ruby_Animation* animation = (const Ruby_Animation*)resource;

	VDPTileManager_LoadTilesToVDPMain(animation->tileData, 
									  animation->numTotalTiles,
									  animation->vdpLocation);



	return 0;
}


u16 Load_StreamedAnimationResource(const Resource* resource)
{
	/*
	const BatchedAnimation* batchedAnimation = (const BatchedAnimation*)resource->resource;

	return VDPTileManager_ReserveSpriteTilesArea(batchedAnimation->maxTilesPerFrame,
												 batchedAnimation->vdpLocation);
												 */

	return 0;
}

u16 Load_PlaneAnimationResource(const Resource* resource)
{
	/*
	const PlaneAnimation* planeAnimation = (const PlaneAnimation*)resource->resource;

	return VDPTileManager_LoadBackgroundTileset(planeAnimation->tileData, 
												planeAnimation->numTotalTiles,
												planeAnimation->vdpLocation);
												*/

	return 0;
}

u16 Load_TileAnimationResource(const Resource* resource)
{
	/*
	const TileAnimation* tileAnimation = (const TileAnimation*)resource->resource;

	return VDPTileManager_LoadBackgroundTileset(tileAnimation->tileData, 
												tileAnimation->tilesPerFrame,
												tileAnimation->vdpLocation);
												*/

	return 0;
}


typedef BOOL (*UpdateAnimationFunctionType)(GameObject* gameObject);

u16 Setup_StandardAnimationResource(GameObject* gameObject, const Resource* resource)
{
	const Ruby_Animation* animation = (const Ruby_Animation*)resource;

	gameObject->animation = animation;
	memcpy(&gameObject->Draw, animation->animationSetup, sizeof(Ruby_AnimationSetup));

	return 0;
}

u16 Setup_StreamedAnimationResource(GameObject* gameObject, const Resource* resource)
{
	/*
	const MetaSpriteAnimation* metaSpriteAnimation = (const MetaSpriteAnimation*)resource->resource;

	gameObject->metaSpriteAnimation = metaSpriteAnimation;
	memcpy(&gameObject->Draw, metaSpriteAnimation->animationSetup, sizeof(AnimationSetup));
	*/

	return 0;
}

u16 Setup_PlaneAnimationResource(GameObject* gameObject, const Resource* resource)
{
	/*
	const PlaneAnimation* planeAnimation = (const PlaneAnimation*)resource->resource;

	gameObject->planeAnimation = planeAnimation;
	gameObject->currentAnimationFrameIndex = 0;
	gameObject->currentPlaneAnimationFrame = planeAnimation->frames[0];
	gameObject->animationTime = gameObject->currentPlaneAnimationFrame->frameTime;
	gameObject->pixelWidth = planeAnimation->tileWidth * TILE_WIDTH;
	gameObject->pixelHeight = planeAnimation->tileHeight * TILE_HEIGHT;
	gameObject->UpdateAnimation = AnimationUtils_updatePlaneAnimation;
	*/

	return 0;
}

u16 Setup_TileAnimationResource(GameObject* gameObject, const Resource* resource)
{
	/*
	const TileAnimation* tileAnimation = (const TileAnimation*)resource->resource;

	gameObject->tileAnimation = tileAnimation;
	gameObject->currentAnimationFrameIndex = 0;
	gameObject->currentTileAnimationFrame = tileAnimation->frames[0];
	gameObject->animationTime = gameObject->currentTileAnimationFrame->frameTime;
	gameObject->UpdateAnimation = AnimationUtils_updateTileAnimation;
	*/
	return 0;
}


void AnimationUtils_UpdateStreamedAnimationFrame(GameObject* gameObject)
{
	/*
	//SMS_setBackdropColor(COLOR_ORANGE);
	const BatchedAnimationFrame* batchedAnimationFrame = gameObject->currentBatchedAnimationFrame;
	const BatchedAnimationSpriteStrip* runner = batchedAnimationFrame->spriteStrips;

	const BatchedAnimation* batchedAnimation = gameObject->batchedAnimation;
	const u8* tileData = batchedAnimation->tileData;
	u8 vdpIndex = *batchedAnimation->vdpLocation;



	do 
	{
		const u8* tileOffset = tileData + (runner->tileIndex << 5);

		// This is actually faster than a look-up table for some reason.
		// Unlike DrawUtils_DrawStreamedBatched which uses one, this function
		// gets slower with one. Maybe because of inlining?
		switch (runner->count)
		{
		case 1:
			UNSAFE_SMS_VRAMmemcpy64(vdpIndex << 5, (const void *)tileOffset);
			break;
		case 2:
		{
			UNSAFE_SMS_VRAMmemcpy128(vdpIndex << 5, (const void *)tileOffset);
			break;
		}
		case 3:
		{
			UNSAFE_SMS_VRAMmemcpy192b(vdpIndex << 5, (const void *)tileOffset);
			break;
		}
		case 4:
			UNSAFE_SMS_VRAMmemcpy256(vdpIndex << 5, (const void *)tileOffset);
		}

		vdpIndex += runner->count << 1;

		runner++;
	} while (runner->count);
	*/
}