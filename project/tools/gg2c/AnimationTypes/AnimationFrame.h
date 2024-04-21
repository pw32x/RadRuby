#pragma once

#include "..\thirdparty\galefile151119\galefile.h"
#include <vector>
#include "..\Base\Options.h"
#include "..\Base\Sprite.h"
#include "AnimationProperties.h"
#include "AnimationTypes.h"

class GraphicsGaleObject; 

class AnimationFrame : public AnimationFrameBase
{
public:
	AnimationFrame();

	void Init(int frameNumber, 
			  const GraphicsGaleObject& ggo, 
	          std::vector<RawSprite>& rawSprites, 
			  std::vector<SpriteProperties>& spriteProperties, 
			  std::vector<SpriteArray>& spriteArrays,
			  const Options& options, 
			  AnimationProperties& animationProperties,
			  int& tileStartIndex);

	int GetSpriteArrayIndex() const { return mSpriteArrayIndex; }
	const std::vector<std::string>& GetFrameTriggerData() const { return mFrameTriggerData; }
	
	int	GetTileCount() const { return mTileCount; }

private:

	void BuildFrame(const GraphicsGaleObject& ggo, AnimationProperties& animationProperties);
	void BuildSprites(const GraphicsGaleObject& ggo, 
	                  std::vector<RawSprite>& rawSprites, 
					  std::vector<SpriteProperties>& spriteProperties, 
					  std::vector<SpriteArray>& spriteArrays,
					  const Options& options, 
					  int& tileStartIndex);

private:

	int				mSpriteArrayIndex;
	int				mTileCount;

	std::vector<std::string>	mFrameTriggerData;
};