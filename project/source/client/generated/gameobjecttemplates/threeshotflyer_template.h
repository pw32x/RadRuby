#ifndef THREESHOTFLYER_TEMPLATE_INCLUDE_H
#define THREESHOTFLYER_TEMPLATE_INCLUDE_H

#include "engine\object_types.h"
#include "client\ai_commands.h"

typedef struct three_shot_flyer_object
{
    GAME_OBJECT_FIELDS;
    AICommandsRunner aiCommandsRunner;
} ThreeShotFlyerObjectType;

#endif
