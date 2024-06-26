#pragma once
#include <string>
#include "..\AnimationTypes\AnimationTypes.h"

#ifdef min 
#undef min 
#endif

#ifdef max 
#undef max
#endif

#include "..\thirdparty\argparse\argparse.hpp"
#include "..\Base\errors.h"

class ProgramArguments
{
public:
    std::string m_filepath = "";
    std::string m_destinationFolder = "";
    AnimationType m_animationType = AnimationType::Standard;
    bool m_updateOnly = false;
    bool m_isStreamed = false;
};

ProgramArguments ParseArguments(int argc, char* argv[]);
