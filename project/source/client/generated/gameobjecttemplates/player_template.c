#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resources.h"

GameObject* Player_Init(GameObject* object, const CreateInfo* createInfo);

const GameObjectTemplate player_template = 
{
    2, // health
    0, // damage
    -3, // rect left
    -12, // rect top
    3, // rect right
    16, // rect bottom
    OBJECTTYPE_PLAYER, // object type
    (const Resource*)&ruby, // resource
    NULL, // extra resources
    Player_Init, // init function
};
