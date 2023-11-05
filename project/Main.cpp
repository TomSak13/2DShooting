// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include "InputSystem.h"

int main(int argc, char** argv)
{
	Game game;
	InputSystem mInputSystem;
	bool success = game.Initialize();
	while (success)
	{
		// ì¸óÕêßå‰
		mInputSystem.ProcessInput(&game);

		// çXêV
		game.UpdateGame();
		if (game.GetState() == Game::EQuit)
		{
			break;
		}

		// ï`âÊ
		game.GenerateOutput();
	}
	game.Shutdown();
	return 0;
}
