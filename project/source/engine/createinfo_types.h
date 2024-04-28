#ifndef CREATEINFO_TYPES_INCLUDE_H
#define CREATEINFO_TYPES_INCLUDE_H

#include "engine/base_types.h"
#include "engine/gameobject_template_types.h"
#include "engine/command_types.h"

#define DECLARE_CREATE_INFO(structname) typedef struct structname \
{\
	 const GameObjectTemplate* gameObjectTemplate;\
	s16 startX;\
	s16 startY;

#define DEC_FIELD(type, name, default_value) type name;
#define END_CREATE_INFO(name) } name;

DECLARE_CREATE_INFO(create_info)
	DEC_FIELD(s8, speedX, 0)
	DEC_FIELD(s8, speedY, 0)
END_CREATE_INFO(CreateInfo)

DECLARE_CREATE_INFO(effect_create_info)
	DEC_FIELD(s8, speedX, 0)
	DEC_FIELD(s8, speedY, 0)
	DEC_FIELD(u8, startFrameNumber, 0)
END_CREATE_INFO(EffectCreateInfo)

DECLARE_CREATE_INFO(commandrunner_create_info)
	DEC_FIELD(const Command*, commands, NULL)
END_CREATE_INFO(CommandRunnerCreateInfo)

#endif