#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resources.h"

GameObject* Enemy_Init(GameObject* object, const CreateInfo* createInfo);

const GameObjectTemplate walker_small_template = 
{
    1, // health
    0, // damage
    -4, // rect left
    -4, // rect top
    4, // rect right
    4, // rect bottom
    OBJECTTYPE_ENEMY, // object type
    (const Resource*)&walker_small, // resource
    NULL, // extra resources
    (InitObjectFunctionType)Enemy_Init, // init function
};
