#pragma once

#include "..\AnimationTypes\AnimationTypes.h"
#include <string>
#include "..\thirdparty\galefile151119\galefile.h"
#include "PlaneAnimationFrame.h"
#include "..\Base\Options.h"
#include "..\GraphicsGale\GraphicsGaleObject.h"
#include <vector>
#include <memory>

class PlaneAnimation : public AnimationBase
{
public:
	PlaneAnimation(const GraphicsGaleObject& ggo, const Options& options);
	void Write(const std::string& outputFolder, const std::string& outputName);

	int GetTileCount() { return m_uniqueTileCount; }
	const BITMAP& GetGeneralBitmapInfo() { return  m_generalBitmapInfo; }

private:
	PlaneAnimationFrame* findSameFrame(const PlaneAnimationFrame& frame);
	int findSameFrameIndex(const PlaneAnimationFrame& frame);

	void WritePlaneAnimationHeaderFile(const std::string& outputFolder, const std::string& outputName);
	void WritePlaneAnimationSourceFile(const std::string& outputFolder, const std::string& outputName);
	void WriteFrameData(const std::string& outputName, std::ofstream& sourceFile);
	void WriteFrameNames(const std::string& outputName, std::ofstream& sourceFile);
	void WritePalettes(const std::string& outputName, std::ofstream& sourceFile);
	void WriteTileMaps(const std::string& outputName, std::ofstream& sourceFile);
	void WriteFrames(const std::string& outputName, std::ofstream& sourceFile);
	void WriteFrameArray(const std::string& outputName, std::ofstream& sourceFile);
	void WriteAnimationStruct(const std::string& outputName, std::ofstream& sourceFile);



private:
	const GraphicsGaleObject&			m_ggo;
	int									m_uniqueTileCount = 0;
	int									m_maxUniqueTilesPerFrame = 0;
	const Options&						m_options;
	BITMAP								m_generalBitmapInfo;
	DWORD								m_numberOfFrames;
	std::vector<PlaneAnimationFrame>  m_frames;
	std::vector<PlaneAnimationFrame*> m_uniqueFrameData;
	std::vector<Tile>					m_tiles;
};