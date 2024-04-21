#pragma once

enum Error
{
	None,
	OpeningGraphicsGaleFileFailed,
	NoFramesInGraphicsGaleFile,
	BitmapHandleIsNull,
	BitmapObjectIsNull,
	NoBitmapFound,
	FormatNot4BitsPerPixel,
	ParsingArgumentsFailed,
	UnsupportedAnimationType,
	UnknownCommandLineFlag
};

#define THROW_ERROR(code, message) \
{\
	std::error_code errorCode(code, std::system_category());\
	throw std::system_error(errorCode, message);\
}

#define THROW_IF_NULL(value, code, message)\
	if (value == nullptr)\
		THROW_ERROR(code, message)

#define THROW_IF_ZERO(value, code, message)\
	if (value == 0)\
		THROW_ERROR(code, message)