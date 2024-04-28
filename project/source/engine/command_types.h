#ifndef COMMAND_TYPES_INCLUDE_H
#define COMMAND_TYPES_INCLUDE_H

#include "genesis.h"
#include "engine\base_types.h"

typedef BOOL (*CommandFunction)(const void* data);

typedef struct 
{
	u16 counter;// counter/timer/scroll pos
	CommandFunction command;
	const void* data;
} Command;

#endif