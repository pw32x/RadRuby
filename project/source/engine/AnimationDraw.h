#ifndef ANIMATION_DRAW_HEADER_H
#define ANIMATION_DRAW_HEADER_H

#include <genesis.h>
#include "animation_types.h"
//#include "engine\ObjectStruct.h"

void Ruby_Animation_Draw(s16 x, s16 y, const Ruby_Animation* animation, u16 frameNumber, u16 tileAttribute);
void Ruby_Animation_DrawNoFlip(s16 x, s16 y, const Ruby_Animation* animation, u16 frameNumber, u16 tileAttribute);

/*
void Ruby_Animation_DrawObject(ObjectStruct* object);
void Ruby_Animation_DrawObjectNoFlip(ObjectStruct* object);

void Ruby_Animation_DrawObjectOnPlane(ObjectStruct* object);

void Ruby_Animation_DrawObjectStub(ObjectStruct* object);
*/
#endif
