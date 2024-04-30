#include "right_scroller_template.h"
#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resources.h"

GameObject* Right_Scroller_Init(RightScrollerObjectType* object, const ScrollerCreateInfo* createInfo);

const GameObjectTemplate right_scroller_template = 
{
    0, // health
    0, // damage
    0, // rect left
    0, // rect top
    0, // rect right
    0, // rect bottom
    OBJECTTYPE_SCROLLER, // object type
    NULL, // resource
    NULL, // extra resources
    (InitObjectFunctionType)Right_Scroller_Init, // init function
};
