#include "shotgun_item_template.h"
#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resources.h"

GameObject* ShotgunItem_Init(ShotgunItemObjectType* object, const CreateInfo* createInfo);

const GameObjectTemplate shotgun_item_template = 
{
    0, // health
    0, // damage
    -8, // rect left
    -8, // rect top
    8, // rect right
    8, // rect bottom
    OBJECTTYPE_ITEM, // object type
    (const Resource*)&shotgun_item, // resource
    NULL, // extra resources
    (InitObjectFunctionType)ShotgunItem_Init, // init function
};
