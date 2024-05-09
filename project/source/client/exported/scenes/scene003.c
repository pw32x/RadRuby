#include "scene003.h"
#include "client\generated\gameobjecttemplates\gameobject_templates.h"
#include "client\generated\resources.h"
#include "engine\object_manager_create.h"
#include "engine\resource_manager.h"
#include "engine\createinfo_types.h"
#include "engine\commandrunner_runall.h"

// command headers
#include "engine\commands\background_commands.h"
#include "engine\commands\set_palette_commands.h"

// create info headers
#include "engine\createinfo_types.h"

const CommandRunnerCreateInfo scene003_createInfoBootstrapper = { &commandrunner_runall_template, 0, 0, NULL };
const ScrollerCreateInfo scene003_createInfo_RightScroller2 = { &right_scroller_template, 0, 97, &field_map, BG_A };
const CommandRunnerCreateInfo scene003_createInfo_CommandRunnerRightScroll6 = { &commandrunner_rightscroll_template, 0, 0, NULL };
const CreateInfo scene003_createInfo_RadRuby7 = { &player_template, 58, 51 };
const CreateInfo scene003_createInfo_Wheeler8 = { &wheeler_template, 120, 99 };
const CreateInfo scene003_createInfo_Wheeler9 = { &wheeler_template, 159, 80 };
const CreateInfo scene003_createInfo_ThreeShotFlyer10 = { &threeshotflyer_template, 220, 44 };

const Command scene003_commands[] = 
{
    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfoBootstrapper },
    { 0, (CommandFunction)ResourceManager_LoadResource, &field_map },
    { 0, (CommandFunction)ResourceManager_LoadResource, &ruby },
    { 0, (CommandFunction)ResourceManager_LoadResource, &explosion },
    { 0, (CommandFunction)ResourceManager_LoadResource, &impact },
    { 0, (CommandFunction)ResourceManager_LoadResource, &bullet },
    { 0, (CommandFunction)ResourceManager_LoadResource, &shotgun },
    { 0, (CommandFunction)ResourceManager_LoadResource, &wheeler },
    { 0, (CommandFunction)ResourceManager_LoadResource, &threeshotflyer },
    { 0, (CommandFunction)ResourceManager_LoadResource, &enemy_bullet },
    { 0, (CommandFunction)SetPalette0, &global_palette },
    { 0, (CommandFunction)SetPalette1, &global_palette },
    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo_RightScroller2 },
    { 0, (CommandFunction)SetPalette2, &global_palette },
    { 0, (CommandFunction)SetBackgroundVerticalScroll, (const void*)4 },
    { 0, (CommandFunction)SetPalette3, &global_palette },
    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo_CommandRunnerRightScroll6 },
    { 61, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo_RadRuby7 },
    { 124, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo_Wheeler8 },
    { 163, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo_Wheeler9 },
    { 232, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo_ThreeShotFlyer10 },
    { 0, (CommandFunction)NULL, NULL}
};

const Scene scene003 = 
{
    scene003_commands,
};
