#pragma once

#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "..\Base\Sprite.h"
#include <vector>
#include <string>
#include <fstream>

void WriteTileData(const std::string& outputName, std::ofstream& sourceFile, int tileCount, const std::vector<RawSprite>& sprites);

std::string BuildFrameName(const std::string& outputName, int frameNumber);
std::string BuildSpriteArrayName(const std::string& outputName, int index);
std::string BuildSpriteName(const std::string outputName, int spritenumber);

DWORD ConvertToTileDataRow(int x, int y, int tileWidth, const BYTE* spriteImageData);
std::string WriteDWORDAsUShort(DWORD value);