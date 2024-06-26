#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resources.h"

GameObject* Shotgun_Init(GameObject* object, const WeaponCreateInfo* createInfo);

const GameObjectTemplate shotgun_template = 
{
    0, // health
    2, // damage
    -6, // rect left
    -6, // rect top
    6, // rect right
    6, // rect bottom
    OBJECTTYPE_PROJECTILE, // object type
    (const Resource*)&shotgun, // resource
    NULL, // extra resources
    (InitObjectFunctionType)Shotgun_Init, // init function
};
