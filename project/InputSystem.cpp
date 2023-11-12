// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
#include "InputSystem.h"
#include "Game.h"
#include <GL/glew.h>
#include <algorithm>
#include "Actor.h"
#include "PauseMenu.h"

InputSystem::InputSystem()
{

}

InputSystem::~InputSystem()
{
	
}

void InputSystem::ProcessInput(Game* game)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			game->SetState(Game::GameState::EQuit);
			break;
		case SDL_KEYDOWN:
			if (!event.key.repeat)
			{
				// UI‚É“ü—Í‚ğ“n‚·‚©AƒQ[ƒ€“à‚É“ü—Í‚ğ“n‚·‚©‚ğƒXƒe[ƒg‚Å”»’f
				if (game->GetState() == Game::GameState::EGameplay)
				{
					//HandleKeyPress(event.key.keysym.sym);
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						new PauseMenu(game);
					}
				}
				else if (!game->GetUIStack().empty())
				{
					game->GetUIStack().back()->
						HandleKeyPress(event.key.keysym.sym);
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (!game->GetUIStack().empty())
			{
				game->GetUIStack().back()->
					HandleKeyPress(event.button.button);
			}
			break;
		default:
			break;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState(NULL);


	if (game->GetState() == Game::GameState::EGameplay)
	{
		game->SetUpdatingActors(true);
		std::vector<class Actor*> Actors = game->GetActors();
		for (auto actor : Actors)
		{
			actor->ProcessInput(keyState);
		}
		game->SetUpdatingActors(false);
	}
	else if (!game->GetUIStack().empty())
	{
		game->GetUIStack().back()->ProcessInput(keyState); // Åã‘w‚É“ü—Í‚ğ“n‚·
	}
}