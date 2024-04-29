#ifndef ANIMATION_DRAW_HEADER_H
#define ANIMATION_DRAW_HEADER_H

#include <genesis.h>
#include "engine\animation_types.h"
#include "engine\object_types.h"

void Animation_Draw(s16 x, s16 y, const Ruby_Animation* animation, u16 frameNumber, u16 tileAttribute);
void Animation_DrawNoFlip(s16 x, s16 y, const Ruby_Animation* animation, u16 frameNumber, u16 tileAttribute);

void Animation_DrawObject(GameObject* object);
void Animation_DrawObjectNoFlip(GameObject* object);

void Animation_DrawObjectOnPlane(GameObject* object);

void Animation_DrawObjectStub(GameObject* object);

#endif
