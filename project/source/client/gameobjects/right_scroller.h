#ifndef RIGHT_SCROLLER_INCLUDE_H
#define RIGHT_SCROLLER_INCLUDE_H

#include "client/generated/gameobjecttemplates/right_scroller_template.h"

#include "engine/object_types.h"
#include "engine/map_types.h"
#include "engine/createinfo_types.h"


GameObject* Right_Scroller_Init(RightScrollerObjectType* object, const ScrollerCreateInfo* createInfo);

#endif