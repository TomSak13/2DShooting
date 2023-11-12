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
	mGame->SetState(Game::GameState::EPaused);
	SetRelativeMouseMode(false);
	SetTitle("GAME OVER");
	AddButton("QuitButton", [this]() { 
				mGame->SetState(Game::GameState::EQuit);
	}); // �����_���֐��Œǉ�
}

GameOverMenu::~GameOverMenu()
{
	SetRelativeMouseMode(true);
	mGame->SetState(Game::GameState::EGameplay);
}

void GameOverMenu::HandleKeyPress(int key)
{
	UIScreen::HandleKeyPress(key);
	
	if (key == SDLK_ESCAPE)
	{
		Close();
	}
}
