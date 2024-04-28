#include "commandrunner_runall.h"
#include "engine/command_manager.h"
#include "engine/object_utils.h"

const GameObjectTemplate commandrunner_runall_template = 
{
	0, // health
	0, // damage
	0, // rect left
	0, // rect top
	0, // rect right
	0, // rect bottom
	OBJECTTYPE_COMMANDRUNNER, // object type
	NULL, // resource info
	NULL, // resource infos
	(InitObjectFunctionType)CommandRunner_RunAll_Init, // init function
};

GameObject* CommandRunner_RunAll_Init(GameObject* object, const CommandRunnerCreateInfo* createInfo)
{
	kprintf("CommandRunner_RunAll_Init\n");

	UNUSED(createInfo);

	kprintf("**************************\n");

	const Command* runner = CommandManager_currentCommand;
	while (runner->command != NULL)
	{
		kprintf("command counter %d\n", runner->counter);
		runner++;
	}

	kprintf("**************************\n");

	// move to the next command because the current one is
	// the one that created us.
	CommandManager_currentCommand++;

	//u8 objectId = object->objectId;

	while (CommandManager_currentCommand->command != NULL)
	{
		kprintf("running command %04lx\n", (u32)CommandManager_currentCommand->command);

		kprintf("command counter: %d\n", CommandManager_currentCommand->counter);

		CommandManager_currentCommand->command(CommandManager_currentCommand->data);

		/*
		// check if the command runner changed while processing the
		// commands.
		if (objectId != object->objectId)
		{
			kprintf("command runner changed\n");
			return NULL;
		}
		*/

		CommandManager_currentCommand++;

		kprintf("finished running command\n");
	}

	object->Update = ObjectUtils_gameObjectDoNothing;

	kprintf("CommandRunner_RunAll_Init end\n");

	return NULL;
}



