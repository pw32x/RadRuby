#include "Debug.h"

#include <vdp.h>
#include <tools.h>


void Assert(u16 condition, const char* message)
{
    if (!condition)
    {
        VDP_init();
        VDP_drawText("Assert!", 0, 0);
        VDP_drawText(message, 0, 1);
		kprintf((char*)message);

        while(1);
    }
}