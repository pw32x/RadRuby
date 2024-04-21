#pragma once

#include "AnimationFrame.h"

#include "AnimationProperties.h"
#include "AnimationTypes.h"
#include <string>

class GraphicsGaleObject;

class Palette : public AnimationBase
{
public:
	Palette(const GraphicsGaleObject& ggo);
	void Write(const std::string& outputFolder, const std::string& outputName);

private:

	void WritePaletteValues(const std::string& outputName, std::ofstream& sourceFile);
	void WritePaletteResource(const std::string& outputName, std::ofstream& sourceFile);

	void WritePaletteHeaderFile(const std::string& outputFolder, const std::string& outputName);
	void WritePaletteSourceFile(const std::string& outputFolder, const std::string& outputName);

private:
	const GraphicsGaleObject&		m_ggo;
};

