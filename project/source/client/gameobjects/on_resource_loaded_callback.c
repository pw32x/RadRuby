#include "on_resource_loaded_callback.h"

//#include "tile_animator.h"
#include "engine\base_types.h"

void* OnResourceLoaded(const Resource* resource)
{
	UNUSED(resource);
	/*
	u8 resourceType = resource->resourceType;


	switch (resourceType)
	{
	case TILE_ANIMATION_RESOURCE_TYPE:
		TileAnimator_Init(resource);
		break;
	}
	*/

	return NULL;
}