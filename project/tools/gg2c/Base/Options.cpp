#include "..\stdafx.h"
#include "Options.h"
#include <string>

Options::Options() 
: mNoLoop(false),
  mSliceSpritesOnGrid(false),
  mSliceWidth(DEFAULT_SLICE_SIZE),
  mSliceHeight(DEFAULT_SLICE_SIZE),
  mCutSliceAsFrame(false),
  mFixedBack(false)
{

}

void Options::ProcessOptions(const std::string& filename)
{
    mNoLoop = (filename.find(".noloop.") != std::string::npos);

	const char* sliceOnGridName = ".sliceongrid";
	int sliceOnGridIndex = filename.find(sliceOnGridName);
    mSliceSpritesOnGrid = (sliceOnGridIndex != std::string::npos);

	if (mSliceSpritesOnGrid)
	{
		int widthStartIndex = sliceOnGridIndex + strlen(sliceOnGridName);
		int widthEndIndex = filename.find('x', widthStartIndex);

		std::string widthString = filename.substr(widthStartIndex, widthEndIndex - widthStartIndex);

		mSliceWidth = std::atoi(widthString.c_str());

		int heightStartIndex = widthEndIndex + 1;
		int heightEndIndex = filename.find('.', heightStartIndex);

		std::string heightString = filename.substr(heightStartIndex, heightEndIndex - heightStartIndex);

		mSliceHeight = std::atoi(heightString.c_str());
	}



	mFixedBack = (filename.find(".fixedback.") != std::string::npos);

	mCutSliceAsFrame = (filename.find(".cutsliceasframe.") != std::string::npos);

	mRemoveDuplicates = (filename.find(".nodedupe") == std::string::npos);
}