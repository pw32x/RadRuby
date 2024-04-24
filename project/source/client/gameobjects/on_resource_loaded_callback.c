#include "on_resource_loaded_callback.h"

//#include "tile_animator.h"

void* OnResourceLoaded(const Resource* resource)
{
	u8 resourceType = resource->resourceType;

	/*
	switch (resourceType)
	{
	case TILE_ANIMATION_RESOURCE_TYPE:
		TileAnimator_Init(resource);
		break;
	}
	*/

	return NULL;
}