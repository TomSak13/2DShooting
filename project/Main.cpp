// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include "MetaAI.h"
#include "InputSystem.h"
#include "Renderer.h"

float ajustDeltaTime(Uint32 tick)
{
	float delta;

	while (!SDL_TICKS_PASSED(SDL_GetTicks(), tick + 16))
		;

	delta = (SDL_GetTicks() - tick) / 1000.0f;
	if (delta > 0.05f)
	{
		delta = 0.05f;
	}

	return delta;
}

int main(int argc, char** argv)
{
	Game game;
	InputSystem inputSystem;
	Renderer renderer(&game);
	MetaAI metaAI;

	Uint32 tickCount;
	float deltaTime;

	// 初期化
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	if (!renderer.Initialize(1024.0f, 768.0f))
	{
		SDL_Log("Failed to initialize renderer");
		return -1;
	}
	if (!game.Initialize(&renderer))
	{
		SDL_Log("Failed to initialize game");
		return -1;
	}
	metaAI.Initialize(&game);

	tickCount = SDL_GetTicks();
	game.LoadData();

	while (1)
	{
		// FPS調整
		deltaTime = ajustDeltaTime(tickCount);
		tickCount = SDL_GetTicks();

		// 入力制御
		inputSystem.ProcessInput(&game);

		// 更新
		metaAI.Update(deltaTime, &game);
		game.UpdateGame(deltaTime);
		if (game.GetState() == Game::GameState::EQuit)
		{
			break;
		}
		
		// 描画
		renderer.Draw();
	}

	renderer.Shutdown();
	game.Shutdown();

	return 0;
}
