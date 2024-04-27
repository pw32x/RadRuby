#include "wheeler_template.h"
#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resources.h"

GameObject* Wheeler_Init(WheelerObjectType* object, const CreateInfo* createInfo);

const GameObjectTemplate wheeler_template = 
{
    3, // health
    1, // damage
    -4, // rect left
    -15, // rect top
    4, // rect right
    16, // rect bottom
    OBJECTTYPE_ENEMY, // object type
    (const Resource*)&wheeler, // resource
    NULL, // extra resources
    (InitObjectFunctionType)Wheeler_Init, // init function
};
