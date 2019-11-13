#include "engine_pch.h"
#include "systems/inputPoller.h"
#include "include/platform/Windows/GLFWInputPoller.h"

namespace Engine {

#ifdef NG_PLATFORM_WINDOWS
	InputPoller* InputPoller::s_instance = new GLFWInputPoller();
#else
	NG_ASSERT(0, "We only support windows");
#endif

}