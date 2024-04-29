#include "vdptile_manager.h"
#include "engine\debug.h"

u16 vdpRegionTileIndex[NUM_VDP_REGIONS];
u16 vdpRegionMaximum[NUM_VDP_REGIONS];

void VDPTileManager_Init(void)
{
	vdpRegionTileIndex[VDP_REGION_MAIN] = 1;
	vdpRegionTileIndex[VDP_REGION_EXT1] = 0x0680;
	vdpRegionTileIndex[VDP_REGION_EXT2] = 0x783;

	vdpRegionMaximum[VDP_REGION_MAIN] = 0x05ff; // 1536 tiles
	vdpRegionMaximum[VDP_REGION_EXT1] = 0x06ff; // 128 tiles
	vdpRegionMaximum[VDP_REGION_EXT2] = 0x07bf;	// 61 tiles
}

void VDPTileManager_LoadTilesToVDP(u8 region, const u32* tiles, u16 numTiles, u16* vdpLocation)
{
    *vdpLocation = vdpRegionTileIndex[region];
    vdpRegionTileIndex[region] += numTiles;
	Assert(vdpRegionTileIndex[region] < vdpRegionMaximum[region], "VDPTileManager_LoadTilesToVDP too many tiles loaded in vdp region");

	VDP_loadTileData(tiles, *vdpLocation, numTiles, DMA);
	VDP_waitDMACompletion();
}

void VDPTileManager_LoadTilesToVDPMain(const u32* tiles, u16 numTiles, u16* vdpLocation)
{
	VDPTileManager_LoadTilesToVDP(VDP_REGION_MAIN, tiles, numTiles, vdpLocation);
}
