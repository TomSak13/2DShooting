// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. 
// Copyright (C) 2023 Tomohiko Sakaguchi
// 
// All rights reserved.
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include <GL/glew.h>
#include <algorithm>
#include "Random.h"

#include "MetaAI.h"
#include "Actor.h"
#include "Ship.h"
#include "EnemyShip.h"
#include "Asteroid.h"

#include "SpriteComponent.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"

#include "UIScreen.h"
#include "Font.h"
#include "TitleMenu.h"
#include "PauseMenu.h"
#include "HUD.h"
#include "BGSpriteComponent.h"
#include "GameOverMenu.h"

Game::Game()
:mRenderer(nullptr)
,mMetaAI(nullptr)
,mGameState(EStart)
,mUpdatingActors(false)
,mPlayerDestroyAsteroid(0)
,mPlayerDestroyShip(0)
{
	
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL_ttf.");
		return false;
	}
	
	mRenderer = new Renderer(this);
	if (!mRenderer->Initialize(1024.0f, 768.0f))
	{
		SDL_Log("Failed to initialize renderer");
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	}

	LoadData();

	mTicksCount = SDL_GetTicks();
	
	return true;
}

void Game::RunLoop()
{
	while (mGameState != EQuit)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mGameState = EQuit;
				break;
			case SDL_KEYDOWN:
				if (!event.key.repeat)
				{
					// UI‚É“ü—Í‚ð“n‚·‚©AƒQ[ƒ€“à‚É“ü—Í‚ð“n‚·‚©‚ðƒXƒe[ƒg‚Å”»’f
					if (mGameState == EGameplay)
					{
						//HandleKeyPress(event.key.keysym.sym);
						if (event.key.keysym.sym == SDLK_ESCAPE)
						{
							new PauseMenu(this);
						}
					}
					else if (!mUIStack.empty())
					{
						mUIStack.back()->
							HandleKeyPress(event.key.keysym.sym);
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (mGameState == EGameplay)
				{
					//HandleKeyPress(event.button.button);
				}
				else if (!mUIStack.empty())
				{
					mUIStack.back()->
						HandleKeyPress(event.button.button);
				}
				break;
			default:
				break;
		}
	}
	
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	

	if (mGameState == EGameplay)
	{
		mUpdatingActors = true;
		for (auto actor : mActors)
		{
			actor->ProcessInput(keyState);
		}
		mUpdatingActors = false;
	}
	else if(!mUIStack.empty())
	{
		mUIStack.back()->ProcessInput(keyState); // Åã‘w‚É“ü—Í‚ð“n‚·
	}
}

void Game::UpdateGame()
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	if (mGameState == EGameplay)
	{
		// Update all actors
		mUpdatingActors = true;
		for (auto actor : mActors)
		{
			actor->Update(deltaTime);
		}
		mUpdatingActors = false;

		// Move any pending actors to mActors
		for (auto pending : mPendingActors)
		{
			pending->ComputeWorldTransform();
			mActors.emplace_back(pending);
		}
		mPendingActors.clear();

		// Add any dead actors to a temp vector
		std::vector<Actor*> deadActors;
		for (auto actor : mActors)
		{
			if (actor->GetState() == Actor::EDead)
			{
				deadActors.emplace_back(actor);
			}
		}

		// Delete dead actors (which removes them from mActors)
		for (auto actor : deadActors)
		{
			delete actor;
		}

		// Player ship's dead check
		if (mShip == NULL)
		{
			new GameOverMenu(this);
		}
	}

	// Update UI screens(ƒXƒ^ƒbƒN‚³‚ê‚½UI‚ðXV)
	for (auto ui : mUIStack)
	{
		if (ui->GetState() == UIScreen::EActive)
		{
			ui->Update(deltaTime);
		}
	}
	// Delete any UIScreens that are closed
	auto iter = mUIStack.begin();
	while (iter != mUIStack.end())
	{
		if ((*iter)->GetState() == UIScreen::EClosing)
		{
			delete* iter;
			iter = mUIStack.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void Game::GenerateOutput()
{
	mRenderer->Draw();
}

void Game::CreateBackGround()
{
	// ”wŒi—pƒAƒNƒ^[
	Actor* bgActor = new Actor(this);
	bgActor->SetPosition(Vector2(0, 0));
	// ”wŒi‚»‚Ì1
	BGSpriteComponent* bgsc = new BGSpriteComponent(bgActor);
	bgsc->SetBGTextures(std::vector<Texture*>{
		mRenderer->GetTexture("Assets/Farback01.png")});

	// ”wŒi‚»‚Ì2
	BGSpriteComponent* bgsc2 = new BGSpriteComponent(bgActor, 50);
	bgsc2->SetBGTextures(std::vector<Texture*>{
		mRenderer->GetTexture("Assets/Stars.png"),
			mRenderer->GetTexture("Assets/Stars.png")});
	bgsc2->SetScrollSpeed(-200.0f);
}

void Game::LoadData()
{
	// Create player's ship
	mShip = new Ship(this);
	mShip->SetPosition(Vector2(0.0f,-300.0f));
	mShip->SetRotation(Math::PiOver2);

	// Create MetaAI
	mMetaAI = new MetaAI(this);
	mMetaAI->Initialize();

	CreateBackGround();

	// UI elements
	mHUD = new HUD(this);

	// Title Menu
	new TitleMenu(this);
}

void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Clear the UI stack
	while (!mUIStack.empty())
	{
		delete mUIStack.back();
		mUIStack.pop_back();
	}

	if (mRenderer)
	{
		mRenderer->UnloadData();
	}
}

void Game::AddAsteroid(Asteroid* ast)
{
	mAsteroids.emplace_back(ast);
}

void Game::RemoveAsteroid(Asteroid* ast)
{
	auto iter = std::find(mAsteroids.begin(),
		mAsteroids.end(), ast);
	if (iter != mAsteroids.end())
	{
		mAsteroids.erase(iter);
	}
}

void Game::CreateEnemyShip()
{
	// Create enemy's ship
	mEnemyShip = new EnemyShip(this);
	mEnemyShip->SetPosition(Vector2(0.0f, FIELD_LENGTH));
	mEnemyShip->SetRotation(Math::PiOver2 * -1);
}

void Game::Shutdown()
{
	UnloadData();

	if (mRenderer)
	{
		mRenderer->Shutdown();
		delete mRenderer;
	}

	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	// If we're updating actors, need to add to pending
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	// Is it in pending actors?
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::PushUI(UIScreen* screen)
{
	mUIStack.emplace_back(screen);
}

Font* Game::GetFont(const std::string& fileName)
{
	auto iter = mFonts.find(fileName);
	if (iter != mFonts.end())
	{
		return iter->second;
	}
	else
	{
		Font* font = new Font(this);
		if (font->Load(fileName))
		{
			mFonts.emplace(fileName, font);
		}
		else
		{
			font->Unload();
			delete font;
			font = nullptr;
		}
		return font;
	}
}