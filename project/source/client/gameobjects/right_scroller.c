#include "right_scroller.h"
#include "engine/object_utils.h"

GameObject* Right_Scroller_Init(RightScrollerObjectType* object, const ScrollerCreateInfo* createInfo)
{
	UNUSED(createInfo);
	object->Update = ObjectUtils_gameObjectDoNothing;
	object->map = createInfo->map;
	object->plane = createInfo->plane;

	return NULL;
}

