#include "draw_utils.h"

#include "engine/base_defines.h"
#include "engine/object_types.h"
#include "engine/scroll_manager.h"

/*
u8 DrawUtils_spriteCounter;
const BatchedAnimationSpriteStrip* DrawUtils_currentSpriteStrips;
u8 DrawUtils_vdpTileIndex;
s16 DrawUtils_screenX;
s16 DrawUtils_screenY;
*/

#define PARAM_COMBINER(x, tile) ((x<<8)|tile)



void DrawUtils_drawNothing(GameObject* gameObject) { UNUSED(gameObject); }

void DrawUtils_drawMetasprite(GameObject* object)
{
    /*
    MetaSpriteBaseTile = *object->metaSpriteAnimation->vdpLocation;

    SMS_addMetaSprite(object->screenx,
                      object->screeny,
                      object->currentMetaSpriteAnimationFrame->metaSprite);
                      */
}

void DrawUtils_DrawBatched(void)
{
    /*
    // function time: 8.2 - 9.0%, self time 5-6%

	const BatchedAnimationSpriteStrip* runner = DrawUtils_currentSpriteStrips;

DrawUtils_DrawBatched_loop:

    u16 xtileParam = PARAM_COMBINER(DrawUtils_screenX + runner->xOffset, runner->tileIndex + DrawUtils_vdpTileIndex);
    u16 y = DrawUtils_screenY + runner->yOffset;

    switch (runner->count)
    {
    case 1:     SMS_addSprite_f(y, xtileParam);
        break;
    case 2:     SMS_addTwoAdjoiningSprites_f(y, xtileParam);
        break;  
    case 3:     SMS_addThreeAdjoiningSprites_f(y, xtileParam);
        break;
    case 4:     SMS_addFourAdjoiningSprites_f(y, xtileParam);
        break;
    }

    runner++;

    if (!runner->count)
        return;

    goto DrawUtils_DrawBatched_loop;
    */
}


void DrawUtils_DrawStreamedBatched(void)
{
    /*
    const BatchedAnimationSpriteStrip* runner = DrawUtils_currentSpriteStrips;

    int vdpOffset = DrawUtils_vdpTileIndex;

DrawUtils_DrawStreamedBatched_loop:

    drawSprite[runner->count](DrawUtils_screenY + runner->yOffset, 
                                PARAM_COMBINER(DrawUtils_screenX + runner->xOffset, 
                                                vdpOffset));

    vdpOffset += (runner->count << 1);

    runner++;

    if (!runner->count)
        return;

    goto DrawUtils_DrawStreamedBatched_loop;
    */
}

void drawToPlane(void)
{
    /*
    u16 address = ((x << 1) + (y << 6)) + 0x3800;

    while (bufferHeight--)
    {
        __asm di __endasm;
        u8* add = (u8*)&address;
        VDPControlPort2 = add[0];
        VDPControlPort2 = add[1] | (1 << 6);
        __asm ei __endasm;

        u16 value;
        u8* val;

        switch (bufferWidth) // limited to 16 tiles
        {
        case 16: value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 15: value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 14: value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 13: value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 12: value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 11: value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 10: value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 9:  value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 8:  value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 7:  value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 6:  value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 5:  value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 4:  value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 3:  value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 2:  value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 1:  value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        }

        address += 64;
    }
    */
}

void DrawUtils_DrawPlaneAnimationFrame(struct game_object* gameObject) 
{
    /*
    const PlaneAnimation* planeAnimation = gameObject->planeAnimation;
    const PlaneAnimationFrame* frame = gameObject->currentPlaneAnimationFrame;

    x                  = gameObject->x >> 3;
    y                  = gameObject->y >> 3;
    buffer             = frame->frameTilemap;
    bufferWidth        = planeAnimation->tileWidth;
    bufferHeight       = planeAnimation->tileHeight;
    vdpOffset          = *planeAnimation->vdpLocation;

    drawToPlane();
    */
}
