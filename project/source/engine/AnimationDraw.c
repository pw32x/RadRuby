#include "AnimationDraw.h"

#include "vdptypes.h"
#include "vdp_spr.h"
//#include "engine\math\mathutils.h"
//#include "engine\Debug.h"
//#include "Config.h"
//#include "engine\defines.h"

void Ruby_Animation_Draw(s16 x, 
                      s16 y, 
                      const Ruby_Animation* animation, 
                      u16 frameNumber, 
                      u16 tileAttribute)
{
    const Ruby_Frame* frame = *(animation->frames + frameNumber);
	const Ruby_Sprite* const* spritePtr = frame->sprites;
    const Ruby_Sprite* sprite;

    u16 loop = frame->numSprites;

    if (spriteDrawIndex + frame->numSprites > SAT_MAX_SIZE)
    {
        loop = SAT_MAX_SIZE - spriteDrawIndex;
    }

    for (; loop != 0; loop--)
    {
		sprite = *(spritePtr);

        if (GET_DIRECTION(tileAttribute)== DIRECTION_RIGHT)
        {
            currentSpriteDef->x = x + sprite->xoffset + 0x80;
        }
        else
        {
            currentSpriteDef->x = x + sprite->xFlippedOffset + 0x80;
        }

        currentSpriteDef->y = y + sprite->yoffset + 0x80;
        currentSpriteDef->attribut = tileAttribute + sprite->tileAttribute;
        currentSpriteDef->size = sprite->sgdkSpriteSize;
        spriteDrawIndex++;
        currentSpriteDef->link = spriteDrawIndex;

        currentSpriteDef++;
        spritePtr++;
    }
}

void Ruby_Animation_DrawNoFlip(s16 x, 
                            s16 y, 
                            const Ruby_Animation* animation, 
                            u16 frameNumber, 
                            u16 tileAttribute)
{
    const Ruby_Frame* frame = *(animation->frames + frameNumber);

	const Ruby_Sprite* const* spritePtr = frame->sprites;
    const Ruby_Sprite* sprite;

    u16 loop = frame->numSprites;

    if (spriteDrawIndex + frame->numSprites > SAT_MAX_SIZE)
    {
        loop = SAT_MAX_SIZE - spriteDrawIndex;
    }

    for (; loop != 0; loop--)
    {
		sprite = *(spritePtr);

        currentSpriteDef->x = x + sprite->xoffset + 0x80;
        currentSpriteDef->y = y + sprite->yoffset + 0x80;
        currentSpriteDef->attribut = tileAttribute + sprite->tileAttribute;
        currentSpriteDef->size = sprite->sgdkSpriteSize;
        spriteDrawIndex++;
        currentSpriteDef->link = spriteDrawIndex;

        currentSpriteDef++;
        spritePtr++;
    }
}
/*
void Ruby_Animation_DrawObject(ObjectStruct* object)
{
    if (object->currentAnimationFrame == NULL) 
	{
		return;
	}

	const Ruby_Sprite* const* spritePtr = object->currentAnimationFrame->sprites;
	const Ruby_Sprite* sprite;

    u16 loop = object->currentAnimationFrame->numSprites;

    if (spriteDrawIndex + object->currentAnimationFrame->numSprites > SAT_MAX_SIZE)
    {
        loop = SAT_MAX_SIZE - spriteDrawIndex;
    }

    for (; loop != 0; loop--)
    {
		sprite = *(spritePtr);

        if (GET_DIRECTION(object->tileAttribute) == DIRECTION_RIGHT)
        {
            currentSpriteDef->x = object->screenx + sprite->xoffset + 0x80;
        }
        else
        {
            currentSpriteDef->x = object->screenx + sprite->xFlippedOffset + 0x80;
        }

        currentSpriteDef->y = object->screeny + sprite->yoffset + 0x80;
        currentSpriteDef->attribut = object->tileAttribute + sprite->tileAttribute;
        currentSpriteDef->size = sprite->sgdkSpriteSize;
        spriteDrawIndex++;
        currentSpriteDef->link = spriteDrawIndex;

        currentSpriteDef++;
        spritePtr++;
    }
}

void Ruby_Animation_DrawObjectNoFlip(ObjectStruct* object)
{
	const Ruby_Sprite* const* spritePtr = object->currentAnimationFrame->sprites;
    const Ruby_Sprite* sprite;

    u16 loop = object->currentAnimationFrame->numSprites;

    if (spriteDrawIndex + object->currentAnimationFrame->numSprites > SAT_MAX_SIZE)
    {
        loop = SAT_MAX_SIZE - spriteDrawIndex;
    }

    while (loop--)
    {
		sprite = *(spritePtr);

        currentSpriteDef->x = object->screenx + sprite->xoffset + 0x80;
        currentSpriteDef->y = object->screeny + sprite->yoffset + 0x80;
        currentSpriteDef->attribut = object->tileAttribute + sprite->tileAttribute;
        currentSpriteDef->size = sprite->sgdkSpriteSize;
        spriteDrawIndex++;
        currentSpriteDef->link = spriteDrawIndex;

        currentSpriteDef++;
        spritePtr++;
    }
}

void Ruby_Animation_DrawObjectOnPlane(ObjectStruct* object)
{
	s16 screenx = V2P(object->x) - object->background->screenx;
    s16 screeny = V2P(object->y) - object->background->screeny;

	const Ruby_Sprite* const* spritePtr = object->currentAnimationFrame->sprites;
    const Ruby_Sprite* sprite;
    u16 loop = object->currentAnimationFrame->numSprites;

    if (spriteDrawIndex + object->currentAnimationFrame->numSprites > SAT_MAX_SIZE)
    {
        loop = SAT_MAX_SIZE - spriteDrawIndex;
    }

    for (; loop != 0; loop--)
    {
		sprite = *(spritePtr);

        if (GET_DIRECTION(object->tileAttribute) == DIRECTION_RIGHT)
        {
            currentSpriteDef->x = screenx + sprite->xoffset + 0x80;
        }
        else
        {
            currentSpriteDef->x = screenx + sprite->xFlippedOffset + 0x80;
        }

        currentSpriteDef->y = screeny + sprite->yoffset + 0x80;
        currentSpriteDef->attribut = object->tileAttribute + sprite->tileAttribute;
        currentSpriteDef->size = sprite->sgdkSpriteSize;
        spriteDrawIndex++;
        currentSpriteDef->link = spriteDrawIndex;

        currentSpriteDef++;
        spritePtr++;
    }
}


void Ruby_Animation_DrawObjectStub(UNUSED ObjectStruct* object)
{

}*/