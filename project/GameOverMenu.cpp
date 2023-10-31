// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "GameOverMenu.h"
#include "Game.h"
//#include "DialogBox.h"
#include <SDL/SDL.h>

GameOverMenu::GameOverMenu(Game* game)
	:UIScreen(game)
{
	mGame->SetState(Game::EPaused);
	SetRelativeMouseMode(false);
	SetTitle("GAME OVER");
	AddButton("QuitButton", [this]() { 
				mGame->SetState(Game::EQuit);
	}); // ƒ‰ƒ€ƒ_Ž®ŠÖ”‚Å’Ç‰Á
}

GameOverMenu::~GameOverMenu()
{
	SetRelativeMouseMode(true);
	mGame->SetState(Game::EGameplay);
}

void GameOverMenu::HandleKeyPress(int key)
{
	UIScreen::HandleKeyPress(key);
	
	if (key == SDLK_ESCAPE)
	{
		Close();
	}
}
