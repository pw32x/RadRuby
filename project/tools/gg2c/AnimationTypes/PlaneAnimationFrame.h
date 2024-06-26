#pragma once

#include "..\thirdparty\galefile151119\galefile.h"
#include <vector>
#include "..\Base\Options.h"
#include "..\Base\Sprite.h"

class GraphicsGaleObject;

typedef RawSprite Tile;

#define PALETTE_SIZE 16

class PlaneAnimationFrame
{
public:
	PlaneAnimationFrame();
	void Init(int frameNumber, const GraphicsGaleObject& ggo, std::vector<Tile>& tiles, const Options& options, int& uniqueTileCount, int& maxUniqueTileCountPerFrame);

	int frameNumber() const { return m_FrameNumber; }
	int tileWidth() const { return m_tileWidth; }
	int tileHeight() const { return m_tileHeight; } 
	int getFrameDelayTime() const { return m_FrameDelayTime; }
	const std::vector<unsigned short>& frameData() const { return m_frame; }

	bool hasSameFrameData(const PlaneAnimationFrame* frame);

	const PALETTEENTRY* getPalette() const { return m_palette; } 

private:
	void GetFrameDelayTime(const GraphicsGaleObject& ggo);
	void BuildFrame(const GraphicsGaleObject& ggo, std::vector<Tile>& tiles, const Options& options, int& uniqueTileCount, int& maxUniqueTileCountPerFrame);

private:
	int							m_FrameNumber;
	LONG						m_FrameDelayTime;
	int							m_uniqueTileCount;
	std::vector<unsigned short> m_frame;
	int							m_tileWidth;
	int							m_tileHeight;

	PALETTEENTRY				m_palette[PALETTE_SIZE];
};
