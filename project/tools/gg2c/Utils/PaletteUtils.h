#pragma once

#include <string>
#include <windows.h>

class PaletteUtils
{
public:
	static void WritePalette(HPALETTE palette, const std::string& outputFolder, const std::string& outputName);
	static void GetPaletteData(HPALETTE hPalette, PALETTEENTRY* paletteEntries);
};