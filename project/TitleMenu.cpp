// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "TitleMenu.h"
#include "Game.h"
#include <SDL/SDL.h>

TitleMenu::TitleMenu(Game* game)
	:UIScreen(game)
{
	mGame->SetState(Game::EPaused);
	SetRelativeMouseMode(false);
	SetTitle("Shooting Demo");
	AddButton("Game Start", [this]() {
		Close();
	});// ƒ‰ƒ€ƒ_Ž®ŠÖ”‚Å’Ç‰Á
	AddButton("Quit", [this]() { 
		mGame->SetState(Game::EQuit);
	}); // ƒ‰ƒ€ƒ_Ž®ŠÖ”‚Å’Ç‰Á
}

TitleMenu::~TitleMenu()
{
	SetRelativeMouseMode(true);
	mGame->SetState(Game::EGameplay);
}

void TitleMenu::HandleKeyPress(int key)
{
	UIScreen::HandleKeyPress(key);
	
	if (key == SDLK_ESCAPE)
	{
		Close();
	}
}
