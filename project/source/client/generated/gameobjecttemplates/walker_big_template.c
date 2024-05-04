#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resources.h"

GameObject* Enemy_Init(GameObject* object, const CreateInfo* createInfo);

const GameObjectTemplate walker_big_template = 
{
    4, // health
    1, // damage
    -16, // rect left
    -16, // rect top
    16, // rect right
    16, // rect bottom
    OBJECTTYPE_ENEMY, // object type
    (const Resource*)&walker_big, // resource
    NULL, // extra resources
    (InitObjectFunctionType)Enemy_Init, // init function
};
