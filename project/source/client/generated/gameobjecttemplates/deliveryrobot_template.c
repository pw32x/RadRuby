#include "deliveryrobot_template.h"
#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resources.h"

GameObject* DeliveryRobot_Init(DeliveryRobotObjectType* object, const CreateInfo* createInfo);

const GameObjectTemplate deliveryrobot_template = 
{
    3, // health
    1, // damage
    -12, // rect left
    -16, // rect top
    12, // rect right
    16, // rect bottom
    OBJECTTYPE_ENEMY, // object type
    (const Resource*)&deliveryrobot, // resource
    NULL, // extra resources
    (InitObjectFunctionType)DeliveryRobot_Init, // init function
};
