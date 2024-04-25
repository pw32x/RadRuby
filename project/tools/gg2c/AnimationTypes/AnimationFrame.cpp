#include "..\stdafx.h"
#include "AnimationFrame.h"
#include "..\Utils\BitmapUtils.h"
#include "..\Utils\SpriteUtils.h"
#include "..\GraphicsGale\GraphicsGaleObject.h"

//#define MAX_SPRITE_SIZE 32

AnimationFrame::AnimationFrame() 
  : mTileCount(0)
{
}

void AnimationFrame::Init(int frameNumber, 
						  const GraphicsGaleObject& ggo, 
						  std::vector<RawSprite>& rawSprites, 
						  std::vector<SpriteProperties>& spriteProperties, 
						  std::vector<SpriteArray>& spriteArrays,
						  const Options& options, 
						  AnimationProperties& animationProperties,
						  int& tileStartIndex)
{
	mFrameNumber = frameNumber;
	GetGGInfo(ggo, animationProperties);
	BuildFrame(ggo, animationProperties);
	BuildSprites(ggo, rawSprites, spriteProperties, spriteArrays, options, tileStartIndex);
}

void AnimationFrame::BuildFrame(const GraphicsGaleObject& ggo, AnimationProperties& animationProperties)
{
	LONG ggFrameDelayTime = ggo.getFrameInfo(mFrameNumber, 2); // the 2 means frame time?
	mFrameDelayTime = (LONG)(myround((float)ggFrameDelayTime / 17.0f)); // 17 ms per frame

	const int length =  256;
	char frameName[length];
	ggo.getFrameName(mFrameNumber, frameName, length);

	if (strstr(frameName, "FRAME_TRIGGER_SPAWN"))
	{
		char* token = strtok(frameName, " "); 
 		mFrameTriggerData.push_back(token);

		char number[256];

		token = strtok(NULL, " "); 
		int spawnX = atoi(token) - animationProperties.mOffsetX;
		_itoa(spawnX, number, 10);

		mFrameTriggerData.push_back(number);

		token = strtok(NULL, " "); 
		int spawnY = atoi(token) - animationProperties.mOffsetY;
		_itoa(spawnY, number, 10);

		mFrameTriggerData.push_back(number);
	}
	else if (strstr(frameName, "ANIMPROP_"))
	{
		char* token = strtok(frameName, " "); 

		if (strcmp(frameName, "ANIMPROP_OFFSET") == 0)
		{
			token = strtok(NULL, " "); 
			animationProperties.mOffsetX = atoi(token);

			token = strtok(NULL, " "); 
			animationProperties.mOffsetY = atoi(token);
		}
	}
}


void AnimationFrame::BuildSprites(const GraphicsGaleObject& ggo, 
								  std::vector<RawSprite>& rawSprites, 
								  std::vector<SpriteProperties>& spriteProperties, 
								  std::vector<SpriteArray>& spriteArrays,
								  const Options& options, 
								  int& tileStartIndex)
{
	HBITMAP				hBitmap;
	BITMAP				bitmapInfo;

	hBitmap = ggo.getBitmap(mFrameNumber, 0);
	GetObject(hBitmap, sizeof(BITMAP), &bitmapInfo);
	BYTE* byteData = CreateByteDataFromBitmap(bitmapInfo);

	int topMost;
	int bottomMost;

	FindTopAndBottomExtents(byteData, 
							bitmapInfo.bmWidth, 
							bitmapInfo.bmHeight, 
							&topMost, 
							&bottomMost, 
							options.mSliceSpritesOnGrid);

	std::vector<int> spritePropertiesIndexes;

	SliceImageIntoSprites(byteData, 
						  bitmapInfo.bmWidth, 
						  bitmapInfo.bmHeight, 
						  topMost, 
						  bottomMost, 
						  rawSprites, 
						  spriteProperties, 
						  spritePropertiesIndexes, 
						  tileStartIndex, 
						  mTileCount, 
						  options.mSliceSpritesOnGrid,
						  options.mSliceWidth,
						  options.mSliceHeight);

	int spriteArrayIndex = FindSpriteArray(spriteArrays, spritePropertiesIndexes);

	if (spriteArrayIndex == -1)
	{
		spriteArrays.push_back(spritePropertiesIndexes);
		spriteArrayIndex = spriteArrays.size() - 1;
	}

	mSpriteArrayIndex = spriteArrayIndex;

	delete [] byteData;
}