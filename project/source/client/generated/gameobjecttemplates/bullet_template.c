#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resources.h"

GameObject* Bullet_Init(GameObject* object, const WeaponCreateInfo* createInfo);

const GameObjectTemplate bullet_template = 
{
    0, // health
    1, // damage
    -4, // rect left
    -4, // rect top
    4, // rect right
    4, // rect bottom
    OBJECTTYPE_PROJECTILE, // object type
    (const Resource*)&bullet, // resource
    NULL, // extra resources
    (InitObjectFunctionType)Bullet_Init, // init function
};
