#include "genesis.h"
#include "vdp.h"

#include "engine/vdp_types.h"

#include "engine/base_types.h"
#include "engine/base_defines.h"
#include "engine/scene_manager.h"
#include "engine/object_manager.h"
#include "engine/object_manager_vdp.h"
#include "engine/scroll_manager.h"
#include "engine/resource_manager.h"
#include "engine/joystick_manager.h"

#include "client/managers/weapon_manager.h"
#include "client/gameobjects/on_resource_loaded_callback.h"
#include "client/exported/scenes/scene003.h"

#ifndef SCENE_TO_RUN
#define SCENE_TO_RUN scene003
#endif


void SetupSystem() 
{
	VDP_waitVSync();
	VDP_init();
	VDP_setScreenHeight224();
	VDP_setScreenWidth320();
	VDP_setBGAAddress(0xC000);
	VDP_setBGBAddress(0xE000);
	VDP_setWindowAddress(0xB000);
	VDP_setHScrollTableAddress(0xB800);
	VDP_setSpriteListAddress(0xBC00);
	VDP_setPlaneSize(64,32, TRUE);

	JOY_init();
	//FadeManager_Init();

	VDP_waitVSync();

	// register 0x0b sets the scroll mode
	// first two bits sets the horizontal scroll mode (whole layer mode (0x00), tile row mode(0x02), or per-line mode(0x03))
	// third bit (0 or 1) sets the vertical scroll mode (whole layer mode or column mode)
	VDP_setReg(0x0b, 0x02);

	//SetupAudio();
}

/*



void VDP_setAllHorizontalScrollTiles(VDPPlane plan, s16 value)
{
#ifdef WIN32
	u16 addr = VDP_HSCROLL_TABLE;
	if (plan == VDP_PLAN_B) 
		addr += 2;

	u16 *pw = (u16*)&vdpRam[addr];

	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;
	*pw = value; pw += 16;

#else
	vu16 *pw;
	vu32 *pl;
	u16 addr;

	// Point to vdp port 
	pw = (u16 *) VDP_DATA_PORT;
	pl = (u32 *) VDP_CTRL_PORT;

	addr = VDP_HSCROLL_TABLE;
	if (plan == VDP_BG_B) addr += 2;

	VDP_setAutoInc(32);
	*pl = VDP_WRITE_VRAM_ADDR(addr);

	// 28 tiles
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
	*pw = value;
#endif
}
*/
int main(bool hardReset)
{
	kprintf("**********************************\n");
	kprintf("**********************************\n");
	kprintf("**********************************\n");

	SetupSystem();

	kprintf("resource manager init\n");
	ResourceManager_Init((OnResourceLoadedCallback)OnResourceLoaded);

	kprintf("weapon manager init\n");
	WeaponManager_InitGame();

	kprintf("scene manager init\n");
	SceneManager_Init(&SCENE_TO_RUN);
		
	kprintf("game loop start\n");

	// game loop
	for(;;) 
	{ 
		kprintf("*** start frame\n");
		JoystickManager_Update();
		MyVDP_resetSprites();
		//GGAnimation_Draw(128, 84, &ruby, 0, vdpAnimationTileIndex);
		ObjectManager_Update();
		MyVDP_setLastSprite();
		kprintf("*** wait for vsync\n");
		// VBLANK
		VDP_waitVSync();
		kprintf("*** vsync period\n");
		SYS_doVBlankProcess();
		VDP_updateSprites(highestVDPSpriteIndex, DMA);

		ObjectManager_VDPDraw();

		ScrollManager_UpdateVDP();
		kprintf("*** end frame\n");
	}

	/*
	SetupSystem();

	PAL_setPalette(PAL0, global_palette.palette, DMA);
	VDP_waitDMACompletion();

	VDPTileIndex vdpAnimationTileIndex = 1;
	VDPTileManager_LoadGGAnimationToVDP(0, &ruby, &vdpAnimationTileIndex);

	VDPTileIndex vdpTilesetTileIndex = vdpAnimationTileIndex + ruby.totalTiles;
	VDPTileManager_LoadTilesetDataToVDP(0, &field_tileset, &vdpTilesetTileIndex);

	TerrainManager_Init_Strip(&field_map);

	// bool DMA_transfer(TransferMethod tm, u8 location, void* from, u16 to, u16 len, u16 step);

	u16 leftColumn[32];
	u16 rightColumn[32];

	const u16* mapRunner = field_map.stripMapData;	
	u16* leftColumnRunner = leftColumn;
	u16* rightColumnRunner = rightColumn;

	const Ruby_Tileset* tileset = (const Ruby_Tileset*)field_map.tilesetResource;
	const u16* metatile_lut = tileset->metatile_lut;

	s16 verticalScrollBuffer[20];
	for (int loop = 0; loop < 20; loop++)
		verticalScrollBuffer[loop] = 0;

	*tileset->vdpLocation = vdpTilesetTileIndex;

	//kprintf("map height: %d\n", field_map.mapHeight);

	u16 vdpLocation = *tileset->vdpLocation;


	for (int mapColumn = 0; mapColumn < 20; mapColumn++)
	{
		// go through the map's strip
		for (int loop = 0; loop < field_map.mapHeight; loop++)
		{
			u16 metaTileIndex = (*mapRunner & BLOCK_MASK);
			const u16* metatileData = metatile_lut + (metaTileIndex << 2);

			*leftColumnRunner = metatileData[0] + vdpLocation; leftColumnRunner++;
			*leftColumnRunner = metatileData[2] + vdpLocation; leftColumnRunner++;
			*rightColumnRunner = metatileData[1] + vdpLocation; rightColumnRunner++;
			*rightColumnRunner = metatileData[3] + vdpLocation; rightColumnRunner++;

			// next map item
			mapRunner++;
		}

		leftColumnRunner = leftColumn;
		rightColumnRunner = rightColumn;

		DMA_transfer(DMA, DMA_VRAM, leftColumn, VDP_getPlaneAddress(VDP_BG_A, mapColumn << 1, 0), field_map.mapHeight << 1, planeWidth << 1);
		VDP_waitDMACompletion();

		DMA_transfer(DMA, DMA_VRAM, rightColumn, VDP_getPlaneAddress(VDP_BG_A, (mapColumn << 1) + 1, 0), field_map.mapHeight << 1, planeWidth << 1);
		VDP_waitDMACompletion();
	}

	while (TRUE)
	{
		MyVDP_resetSprites();
		GGAnimation_Draw(128, 84, &ruby, 0, vdpAnimationTileIndex);

		MyVDP_setLastSprite();
		VDP_waitVSync();
		VDP_updateSprites(highestVDPSpriteIndex, DMA);
		VDP_setAllHorizontalScrollTiles(BG_A, 0);
		VDP_setVerticalScrollTile(BG_A, 0, verticalScrollBuffer, 20, DMA);
		SYS_doVBlankProcess();
	}
	*/

	return 0;
}