#ifndef RIGHT_SCROLLER_TEMPLATE_INCLUDE_H
#define RIGHT_SCROLLER_TEMPLATE_INCLUDE_H

#include "engine\object_types.h"
#include "engine\map_types.h"

typedef struct right_scroller_object
{
    GAME_OBJECT_FIELDS;
    const Ruby_StripMap* map;
    u8 plane;
} RightScrollerObjectType;

#endif
