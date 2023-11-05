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
		// ���͐���
		mInputSystem.ProcessInput(&game);

		// �X�V
		game.UpdateGame();
		if (game.GetState() == Game::EQuit)
		{
			break;
		}

		// �`��
		game.GenerateOutput();
	}
	game.Shutdown();
	return 0;
}
