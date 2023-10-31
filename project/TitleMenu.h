// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "UIScreen.h"

class TitleMenu : public UIScreen
{
public:
	TitleMenu(class Game* game);
	~TitleMenu();

	void HandleKeyPress(int key) override;
};
