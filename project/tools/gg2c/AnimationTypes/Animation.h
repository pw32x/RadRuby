#pragma once

#include "AnimationTypes.h"
#include "AnimationFrame.h"
#include "AnimationProperties.h"
#include "..\GraphicsGale\GraphicsGaleObject.h"
#include <string>

class Animation : public AnimationBase
{
public:
	Animation(const GraphicsGaleObject& ggo, const Options& options);
	void Write(const std::string& outputFolder, const std::string& outputName);

	int GetTileCount() { return m_tileCount; }

	const BITMAP& GetGeneralBitmapInfo() { return  m_generalBitmapInfo; }

private:
	void WriteSpritesData(const std::string& outputName, std::ofstream& sourceFile);
	void WriteFrameSpriteArrayData(const std::string& outputName, std::ofstream& sourceFile);
	void WriteFrames(const std::string& outputName, std::ofstream& sourceFile);
	void WriteFrameArray(const std::string& outputName, std::ofstream& sourceFile);
	void WriteAnimationStruct(const std::string& outputName, std::ofstream& sourceFile);

	void WriteAnimationHeaderFile(const std::string& outputFolder, const std::string& outputName);
	void WriteAnimationSourceFile(const std::string& outputFolder, const std::string& outputName);

private:
	const GraphicsGaleObject&		m_ggo;

	std::vector<AnimationFrame>		m_frames;
	std::vector<RawSprite>			m_rawSprites;
	std::vector<SpriteProperties>	m_spriteProperties;
	std::vector<SpriteArray>		m_spriteArrays;
	bool							mHasFrameTriggerData;
	int								m_tileCount = 0;
	int								m_totalFrameTime = 0;
	int								m_maxTilesInFrame = 0;
	const Options&					m_options;
	AnimationProperties				m_animationProperties;
	BITMAP							m_generalBitmapInfo;
};