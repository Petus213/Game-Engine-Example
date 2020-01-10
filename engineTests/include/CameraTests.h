#pragma once
#include <gtest\gtest.h>
#include "windows\Camera.h"
#include "windows\PerspectiveCamera3D.h"

Engine::PerspectiveCamera3D Cc;

bool OnControlTrue(Engine::PerspectiveCamera3D& e)
{
	return true;
}

bool onControlFalse(Engine::PerspectiveCamera3D& e)
{
	return false;
}


