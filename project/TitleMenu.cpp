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
	mGame->SetState(Game::GameState::EPaused);
	SetRelativeMouseMode(false);
	SetTitle("Shooting Demo");
	AddButton("Game Start", [this]() {
		Close();
	});// ラムダ式関数で追加
	AddButton("Quit", [this]() { 
		mGame->SetState(Game::GameState::EQuit);
	}); // ラムダ式関数で追加
}

TitleMenu::~TitleMenu()
{
	SetRelativeMouseMode(true);
	mGame->SetState(Game::GameState::EGameplay);
}

void TitleMenu::HandleKeyPress(int key)
{
	UIScreen::HandleKeyPress(key);
	
	if (key == SDLK_ESCAPE)
	{
		Close();
	}
}
