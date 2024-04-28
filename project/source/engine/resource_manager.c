#include "resource_manager.h"
#include "engine/resource_types.h"

//#include <string.h>

#include "engine/base_types.h"
#include "engine/base_defines.h"
#include "engine/animation_utils.h"
#include "engine/map_load.h"

typedef void* (*LoadFunc)(const Resource* resource);
typedef void* (*SetupFunc)(struct game_object* gameObject, const Resource* resource);

LoadFunc ResourceManager_loadFunctions[NUM_RESOURCE_TYPES];
SetupFunc ResourceManager_setupFunctions[NUM_RESOURCE_TYPES];

OnResourceLoadedCallback ResourceManager_onResourceLoadedCallback = NULL;

void printResourceTypeName(u8 resourceType)
{
	switch (resourceType)
	{
	case STANDARD_ANIMATION_RESOURCE_TYPE			: MSG("Standard Animation"); return;
	case STREAMED_ANIMATION_RESOURCE_TYPE			: MSG("Streamed Animation"); return;
	case PLANE_ANIMATION_RESOURCE_TYPE				: MSG("Plane Animation"); return;
	case TILE_ANIMATION_RESOURCE_TYPE				: MSG("Tile Animation"); return;
	case MAP_RESOURCE_TYPE							: MSG("Map"); return;
	case STRIP_MAP_RESOURCE_TYPE					: MSG("StripMap"); return;
	case TILESET_RESOURCE_TYPE						: MSG("Tileset"); return;
	case ANIMATED_TILESET_RESOURCE_TYPE				: MSG("Animated Tileset"); return;
	}

	MSG("Unknown");
}

void ResourceManager_Init(OnResourceLoadedCallback onResourceLoadedCallback)
{
	memset(ResourceManager_loadFunctions, 0, sizeof(ResourceManager_loadFunctions));
	memset(ResourceManager_setupFunctions, 0, sizeof(ResourceManager_setupFunctions));

	// Load
	ResourceManager_loadFunctions[STANDARD_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_StandardAnimationResource;
	ResourceManager_loadFunctions[STREAMED_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_StreamedAnimationResource;
	ResourceManager_loadFunctions[PLANE_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_PlaneAnimationResource;
	ResourceManager_loadFunctions[TILE_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_TileAnimationResource;
	ResourceManager_loadFunctions[MAP_RESOURCE_TYPE] = (LoadFunc)Load_MapResource;
	ResourceManager_loadFunctions[STRIP_MAP_RESOURCE_TYPE] = (LoadFunc)Load_StripMapResource;
	ResourceManager_loadFunctions[TILESET_RESOURCE_TYPE] = (LoadFunc)Load_TilesetResource;
	ResourceManager_loadFunctions[ANIMATED_TILESET_RESOURCE_TYPE] = (LoadFunc)Load_AnimatedTilesetResource;

	// Setup
	ResourceManager_setupFunctions[STANDARD_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_StandardAnimationResource;
	ResourceManager_setupFunctions[STREAMED_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_StreamedAnimationResource;
	ResourceManager_setupFunctions[PLANE_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_PlaneAnimationResource;
	ResourceManager_setupFunctions[TILE_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_TileAnimationResource;

	ResourceManager_SetOnResourceLoadedCallback(onResourceLoadedCallback);
}

void* ResourceManager_LoadResource(const Resource* resource)
{
	void* value = ResourceManager_loadFunctions[resource->resourceType](resource);

	if (ResourceManager_onResourceLoadedCallback != NULL)
		ResourceManager_onResourceLoadedCallback(resource);

	return value;
}

void* ResourceManager_SetupResource(struct game_object* gameObject, const Resource* resource)
{
	return ResourceManager_setupFunctions[resource->resourceType](gameObject, resource);
}

void ResourceManager_SetOnResourceLoadedCallback(OnResourceLoadedCallback callback)
{
	ResourceManager_onResourceLoadedCallback = callback;
}