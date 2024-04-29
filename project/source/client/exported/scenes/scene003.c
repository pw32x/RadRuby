#include "scene003.h"
#include "client\generated\gameobjecttemplates\gameobject_templates.h"
#include "client\generated\resources.h"
#include "engine\object_manager_create.h"
#include "engine\resource_manager.h"
#include "engine\createinfo_types.h"
#include "engine\commandrunner_runall.h"

// command headers
#include "client\gameobjects\right_scroller.h"
#include "engine\commands\background_commands.h"
#include "engine\commands\set_palette_commands.h"

// create info headers
#include "engine\createinfo_types.h"

const CommandRunnerCreateInfo scene003_createInfoBootstrapper = { &commandrunner_runall_template, 0, 0, NULL };
const CommandRunnerCreateInfo scene003_createInfo1 = { &commandrunner_rightscroll_template, 0, 3, NULL };
const CreateInfo scene003_createInfo7 = { &player_template, 48, 88, 0, 0 };
const CreateInfo scene003_createInfo8 = { &threeshotflyer_template, 80, 53, 0, 0 };
const CreateInfo scene003_createInfo9 = { &wheeler_template, 123, 98, 0, 0 };
const CreateInfo scene003_createInfo10 = { &wheeler_template, 162, 105, 0, 0 };

const Command scene003_commands[] = 
{
    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfoBootstrapper },
    { 0, (CommandFunction)ResourceManager_LoadResource, &ruby },
    { 0, (CommandFunction)ResourceManager_LoadResource, &explosion },
    { 0, (CommandFunction)ResourceManager_LoadResource, &impact },
    { 0, (CommandFunction)ResourceManager_LoadResource, &bullet },
    { 0, (CommandFunction)ResourceManager_LoadResource, &shotgun },
    { 0, (CommandFunction)ResourceManager_LoadResource, &threeshotflyer },
    { 0, (CommandFunction)ResourceManager_LoadResource, &enemy_bullet },
    { 0, (CommandFunction)ResourceManager_LoadResource, &wheeler },
    { 0, (CommandFunction)ResourceManager_LoadResource, &field_map},
    { 0, (CommandFunction)SetBackgroundVerticalScroll, (const void*)4 },
    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo1 },
    { 0, (CommandFunction)SetPalette0, &global_palette },
    { 0, (CommandFunction)SetPalette1, &global_palette },
    { 0, (CommandFunction)SetPalette2, &global_palette },
    { 0, (CommandFunction)SetPalette3, &global_palette },
    { 0, (CommandFunction)RightScroller_Init, &field_map },
    { 51, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo7 },
    { 92, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo8 },
    { 127, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo9 },
    { 166, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo10 },
    { 0, (CommandFunction)NULL, NULL}
};

const Scene scene003 = 
{
    scene003_commands,
};
