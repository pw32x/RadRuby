#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resources.h"

GameObject* BasicEffect_Init(GameObject* object, const EffectCreateInfo* createInfo);

const GameObjectTemplate explosion_template = 
{
    0, // health
    0, // damage
    0, // rect left
    0, // rect top
    0, // rect right
    0, // rect bottom
    OBJECTTYPE_EFFECT, // object type
    (const Resource*)&explosion, // resource
    NULL, // extra resources
    (InitObjectFunctionType)BasicEffect_Init, // init function
};
