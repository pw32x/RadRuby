#include "..\stdafx.h"
#include "Animation.h"
#include "..\Utils\WriteUtils.h"
#include "..\Utils\StringUtils.h"
#include <fstream>
#include <algorithm>
#include <sstream>

Animation::Animation(const GraphicsGaleObject& ggo, const Options& options)
: m_ggo(ggo),
  m_tileCount(0),
  m_maxTilesInFrame(0),
  m_options(options),
  mHasFrameTriggerData(false)
{
	HBITMAP bitmap = m_ggo.getBitmap(0, 0);
	THROW_IF_NULL(bitmap, Error::BitmapHandleIsNull, "Error retrieving bitmap data from Graphics Gale file");
	THROW_IF_ZERO(GetObject(bitmap, sizeof(BITMAP), &m_generalBitmapInfo), Error::BitmapObjectIsNull, "BitmapInfo is NULL");

	unsigned int numberOfFrames = m_ggo.getFrameCount();
	m_frames.resize(numberOfFrames);


	m_maxTilesInFrame = 0;

	/*
    for (DWORD loop = 0; loop < numberOfFrames; loop++)
    {
		AnimationFrame& frame = m_frames[loop];

		frame.Init(loop, ggo, m_rawSprites, m_spriteProperties, m_spriteArrays, m_options, m_animationProperties, m_tileCount);

		int tileCount = frame.GetTileCount();
		if (tileCount > m_maxTilesInFrame)
		{
			m_maxTilesInFrame = tileCount;
		}

		m_totalFrameTime += frame.GetFrameDelayTime();
    }
	*/

    for (DWORD loop = 0; loop < numberOfFrames; loop++)
    {
		AnimationFrame& frame = m_frames[loop];

		frame.Init(loop, ggo, m_rawSprites, m_spriteProperties, m_spriteArrays, m_options, m_animationProperties, m_tileCount);

        m_maxTilesInFrame = max(m_maxTilesInFrame, frame.GetTileCount());

		m_totalFrameTime += frame.GetFrameDelayTime();

        if (loop > 0)
        {
            int previousIndex = loop - 1;

            AnimationFrame& previousFrame = m_frames[previousIndex];

            if (previousFrame.getNextFrameIndex() == AnimationFrameBase::NEXT_FRAME_NOT_SET)
            {
                if (frame.startsAnimation())
                {
                    int animationStartIndex;

                    auto it = m_animationProperties.animationFrameNames.lower_bound(loop);

                    if (it != m_animationProperties.animationFrameNames.begin()) 
                    {
                        --it; // Move the iterator one step back to get the closest key
                        animationStartIndex = it->first;
                    } 
                    else 
                    {
                        animationStartIndex = 0;
                    }

                    previousFrame.setNextFrameIndex(animationStartIndex);
                }
                else
                {
                    previousFrame.setNextFrameIndex(loop);
                }
            }
        }
    }

    int lastFrameIndex = m_frames.size() - 1;

    if (m_frames[lastFrameIndex].getNextFrameIndex() == AnimationFrameBase::NEXT_FRAME_NOT_SET)
    {
        if (!m_frames[lastFrameIndex].startsAnimation())
        {
            auto it = m_animationProperties.animationFrameNames.lower_bound(lastFrameIndex);

            if (it != m_animationProperties.animationFrameNames.begin()) 
            {
                --it; // Move the iterator one step back to get the closest key
                m_frames[lastFrameIndex].setNextFrameIndex(it->first);
            } 
            else 
            {
                m_frames[lastFrameIndex].setNextFrameIndex(0);
            }
        }
        else
        {
            m_frames[lastFrameIndex].setNextFrameIndex(lastFrameIndex);
        }
    }
}

void Animation::Write(const std::string& outputFolder, const std::string& outputName)
{
	WriteAnimationHeaderFile(outputFolder, outputName);
	WriteAnimationSourceFile(outputFolder, outputName);
}

void Animation::WriteAnimationHeaderFile(const std::string& outputFolder, const std::string& outputName)
{
	std::string headerFilename = outputName + ".h";
	std::ofstream headerfile(outputFolder + headerFilename);

    // header guard
    std::string headerGuard = outputName + "_ANIMATION_INCLUDE_H";
    std::transform(headerGuard.begin(), headerGuard.end(), headerGuard.begin(), ::toupper);
    headerfile << "// File generated by gg2c.\n";
    headerfile << "#ifndef " << headerGuard << "\n";
    headerfile << "#define " << headerGuard << "\n";
    headerfile << "\n";

	// includes
    headerfile << "#include \"engine\\animation_types.h\"\n";
    headerfile << "\n";

	// exported types
    headerfile << "RESOURCE() extern const Ruby_Animation " << outputName << ";\n"; 
    headerfile << "\n";

	headerfile << "#define " << StringUtils::str_toupper(outputName) << "_NUMFRAMES " << m_frames.size() << "\n";
	headerfile << "\n";

	if (m_animationProperties.animationFrameNames.size() > 0)
	{
		headerfile << "// frame numbers for specific animations.\n";
		for (const auto& pair : m_animationProperties.animationFrameNames) 
		{
			std::transform(headerGuard.begin(), headerGuard.end(), headerGuard.begin(), ::toupper);
			headerfile << "#define " << StringUtils::str_toupper(outputName) << "_" << StringUtils::str_toupper(pair.second) << "_FRAME_INDEX" << " " << pair.first << "\n";
		}
		headerfile << "\n";
	}

    // end header guard
    headerfile << "#endif\n\n";
    headerfile.close();
}

 

void Animation::WriteSpritesData(const std::string& outputName, std::ofstream& sourceFile)
{
	for (size_t loop = 0; loop < m_spriteProperties.size(); loop++)
	{
		std::string spriteName = BuildSpriteName(outputName, loop);

		const SpriteProperties& properties = m_spriteProperties[loop];
		const RawSprite& rawSprite = m_rawSprites[properties.rawSprite];
		int tileStartIndex = rawSprite.tileStartIndex;

        sourceFile << "const Ruby_Sprite " << spriteName << " = \n";
        sourceFile << "{\n";
        sourceFile << "    " << properties.xPositionOffset - m_animationProperties.mOffsetX << ", // x position offset\n";
        sourceFile << "    " << properties.yPositionOffset - m_animationProperties.mOffsetY  << ", // y position offset\n";
		sourceFile << "    " << properties.xFlippedPositionOffset << ", // x flipped position offset\n";
        sourceFile << "    TILE_ATTR_FULL(PAL0, 0, " << properties.verticalFlip << ", " << properties.horizontalFlip << ", " << tileStartIndex << "), // tile attribute and tile offset in sprite tile data\n";
        sourceFile << "    SPRITE_SIZE(" << rawSprite.tileWidth << ", " << rawSprite.tileHeight << "), // sgdk sprite size\n";
        sourceFile << "};\n\n";
	}
}





void Animation::WriteFrameSpriteArrayData(const std::string& outputName, std::ofstream& sourceFile)
{
	for (size_t loop = 0; loop < m_spriteArrays.size(); loop++)
	{
		const std::vector<int>& spriteArray = m_spriteArrays[loop];

		if (spriteArray.size() == 0)
			continue;

		sourceFile << "const Ruby_Sprite* const " << BuildSpriteArrayName(outputName, loop) << "[" << spriteArray.size() << "] = \n";
		sourceFile << "{\n";		

		for (size_t loop = 0; loop < spriteArray.size(); loop++)
		{
			sourceFile << "    &" << BuildSpriteName(outputName, spriteArray[loop]) << ",\n";
		}

		sourceFile << "};\n\n";		
	}
}





void Animation::WriteFrames(const std::string& outputName, std::ofstream& sourceFile)
{
    // forward declare frame names.
    for (size_t frameLoop = 0; frameLoop < m_frames.size(); frameLoop++)
    {
        sourceFile << "extern const Ruby_Frame " << BuildFrameName(outputName, frameLoop) << ";\n";
    }

	sourceFile << "\n\n";

	int frameTriggerDataCount = 0;
	for (size_t frameLoop = 0; frameLoop < m_frames.size(); frameLoop++)
	{
		const AnimationFrame& frame = m_frames[frameLoop];

		if (frame.GetFrameTriggerData().size() > 0)
		{
			if (frameTriggerDataCount == 0)
			{
				//  print start of array
				sourceFile << "s16 const " << outputName << "FrameTriggerData[] = \n";
				sourceFile << "{\n";
				sourceFile << "	0,\n";
				mHasFrameTriggerData = true;
			}

			for (const auto& frameTriggerData : frame.GetFrameTriggerData())
			{
				sourceFile << "	" << frameTriggerData << ", \n";
			}

			frameTriggerDataCount += frame.GetFrameTriggerData().size();
		}
	}

	if (frameTriggerDataCount > 0)
	{
		// print end of array
		sourceFile << "};\n";
	}

	sourceFile << "\n\n";

	int frameTriggerDataOffset = 1;

	for (size_t frameLoop = 0; frameLoop < m_frames.size(); frameLoop++)
	{
		const AnimationFrame& frame = m_frames[frameLoop];

		sourceFile << "\n";
		sourceFile << "const Ruby_Frame " << BuildFrameName(outputName, frameLoop) << " = \n";
		sourceFile << "{\n";

		const std::vector<int>& spriteArray = m_spriteArrays[frame.GetSpriteArrayIndex()];

		if (spriteArray.size() > 0)
			sourceFile << "    " << BuildSpriteArrayName(outputName, frame.GetSpriteArrayIndex()) << ",\n";
		else
			sourceFile << "    NULL,\n";


		sourceFile << "    " << spriteArray.size() << ", // number of sprites\n";

		if (frame.GetFrameTriggerData().size() > 0)
		{
			sourceFile << "    " << frameTriggerDataOffset << ", // frame trigger data offset\n"; 
			frameTriggerDataOffset += frame.GetFrameTriggerData().size();
		}
		else
		{
			sourceFile << "    0, // frame trigger data offset\n"; 
		}

		sourceFile << "    " << frame.GetFrameDelayTime() << ", // frame time\n"; 

		if (frameLoop + 1 > m_frames.size() - 1)
		{
			if (m_options.mNoLoop)
			{
				sourceFile << "    NULL, // stop animation. no looping\n";
			}
			else
			{
				sourceFile << "    &" << BuildFrameName(outputName, 0) << ", // loop to next frame. \n";
			}
		}
		else
		{
			sourceFile << "    &" << BuildFrameName(outputName, frameLoop + 1) << ", // next frame\n";
		}

		sourceFile << "};\n";
		sourceFile << "\n";

	}
}

void Animation::WriteFrameArray(const std::string& outputName, std::ofstream& sourceFile)
{
    sourceFile << "const Ruby_Frame* const " << outputName << "Frames[" << m_frames.size() << "] = \n";
    sourceFile << "{\n";

    for (size_t loop = 0; loop < m_frames.size(); loop++)
    {
        sourceFile << "    &" << BuildFrameName(outputName, loop) << ",\n";
    }

    sourceFile << "};\n\n";
}

void Animation::WriteAnimationSetup(const std::string& outputName, std::ofstream& sourceFile)
{
    sourceFile << "const Ruby_AnimationSetup const " << outputName << "Setup = \n";
    sourceFile << "{\n";
    sourceFile << "    DrawUtils_drawMetasprite,\n"; //void (*Draw)(struct game_object* gameObject);
    sourceFile << "    AnimationUtils_updateStandardAnimation,\n"; //BOOL (*UpdateAnimation)(struct game_object* gameObject);
    sourceFile << "    &" << outputName << "Frame0,\n"; //const void* startingAnimationFrame;
    sourceFile << "    0,\n"; //u8 startAnimationFrameIndex;
    sourceFile << "    " << m_frames[0].GetFrameDelayTime() << ",\n"; //u8 animationTime;
    sourceFile << "};\n";
}


void Animation:: WriteAnimationStruct(const std::string& outputName, std::ofstream& sourceFile)
{
    // final struct
    sourceFile << "\n";

	sourceFile << "u16 " << outputName << "VdpLocation;\n\n";

    sourceFile << "const Ruby_Animation " << outputName << " = \n";
    sourceFile << "{\n";
	sourceFile << "    STANDARD_ANIMATION_RESOURCE_TYPE,\n";
	sourceFile << "    &" << outputName << "Setup,\n";
    sourceFile << "    " << outputName << "Frames,\n";
    sourceFile << "    " << m_frames.size() << ", // number of frames\n";
    sourceFile << "    " << m_generalBitmapInfo.bmWidth << ", // width in pixels\n";
    sourceFile << "    " << m_generalBitmapInfo.bmHeight << ", // height in pixels\n";
    sourceFile << "    " << m_maxTilesInFrame << ", // max tiles per frame\n";
    sourceFile << "    " << m_tileCount << ", // the total number of tiles in the animation\n";
    sourceFile << "    (const u32*)" << outputName << "TileData, // start of the sprite data\n";

	if (mHasFrameTriggerData)
		sourceFile << "    " <<  outputName << "FrameTriggerData, // frame trigger data blob\n";
	else 
		sourceFile << "    NULL, // frame trigger data blob\n";

	sourceFile << "    &" << outputName << "VdpLocation, // location in vdp when loaded\n";

    sourceFile << "};\n";
}

void Animation::WriteAnimationSourceFile(const std::string& outputFolder, const std::string& outputName)
{
	std::ofstream sourceFile(outputFolder + outputName + ".c");

    // includes
    sourceFile << "#include <genesis.h>\n";
    sourceFile << "#include \"" << outputName << ".h\"\n";
	sourceFile << "#include \"engine\\FrameTriggers.h\"\n";
	sourceFile << "#include \"engine\\draw_utils.h\"\n";
	sourceFile << "#include \"engine\\animation_utils.h\"\n";
	
    sourceFile << "\n";
    sourceFile << "\n";

	// tile data
	WriteTileData(outputName, sourceFile, m_tileCount, m_rawSprites);

	// sprites
	WriteSpritesData(outputName, sourceFile);

	// frames sprite arrays
	WriteFrameSpriteArrayData(outputName, sourceFile);

	// frames
	WriteFrames(outputName, sourceFile);

	// frame array
	WriteFrameArray(outputName, sourceFile);

	// animation setup
	WriteAnimationSetup(outputName, sourceFile);

	// animation
	WriteAnimationStruct(outputName, sourceFile);

    sourceFile.close();
}