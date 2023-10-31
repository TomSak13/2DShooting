// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "UIScreen.h"

class GameOverMenu : public UIScreen
{
public:
	GameOverMenu(class Game* game);
	~GameOverMenu();

	void HandleKeyPress(int key) override;
};
