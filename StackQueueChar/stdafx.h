#ifndef __STDAFX__
#define __STDAFX__

#if _DEBUG
	#pragma comment(lib, "../ConsoleEngine/ConsoleEngineDebug.lib")
#else
	#pragma comment(lib, "../ConsoleEngine/ConsoleEngineRelease.lib")
#endif
#include "../ConsoleEngine/ConsoleEngine.h"

#include <stack>
#include <queue>
#include <ctime>
#include <algorithm>

#endif // !__STDAFX__
