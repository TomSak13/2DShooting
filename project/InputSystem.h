// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Game.h"

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void ProcessInput(Game* game);
	
private:
};
