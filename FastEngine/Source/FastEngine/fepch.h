#pragma once
#pragma message("Compiling precompiled headers. \n")

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>


#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "FastEngine/Core.h":
#include "FastEngine/Log.h"

#ifdef FE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
