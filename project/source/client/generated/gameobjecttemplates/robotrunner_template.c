#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resources.h"

GameObject* Enemy_Init(GameObject* object, const CreateInfo* createInfo);

const GameObjectTemplate robotrunner_template = 
{
    3, // health
    1, // damage
    -9, // rect left
    -15, // rect top
    9, // rect right
    16, // rect bottom
    OBJECTTYPE_ENEMY, // object type
    (const Resource*)&robotrunner, // resource
    NULL, // extra resources
    Enemy_Init, // init function
};
