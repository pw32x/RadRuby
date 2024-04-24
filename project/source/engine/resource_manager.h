#ifndef RESOURCE_MANAGER_INCLUDE_H
#define RESOURCE_MANAGER_INCLUDE_H

#include "genesis.h"
#include "engine/base_types.h"
#include "engine/resource_types.h"

struct game_object;

typedef void* (*OnResourceLoadedCallback)(const Resource* resource);

void ResourceManager_Init(OnResourceLoadedCallback callback);

void* ResourceManager_LoadResource(const Resource* resource);
void* ResourceManager_SetupResource(struct game_object* gameObject, const Resource* resource);


void ResourceManager_SetOnResourceLoadedCallback(OnResourceLoadedCallback callback);

#endif