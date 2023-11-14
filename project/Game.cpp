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
#include <SDL/SDL_ttf.h>
#include "Random.h"
#include "InputSystem.h"

#include "MetaAI.h"
#include "Actor.h"
#include "Ship.h"
#include "EnemyShip.h"
#include "Asteroid.h"

#include "CollisionBroker.h"

#include "SpriteComponent.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"

#include "UIScreen.h"
#include "TitleMenu.h"
#include "PauseMenu.h"
#include "HUD.h"
#include "BGSpriteComponent.h"
#include "GameOverMenu.h"

Game::Game()
:mRenderer(nullptr)
,mGameState(GameState::EStart)
,mUpdatingActors(false)
,mCollisionBroker(nullptr)
,mHUD(nullptr)
,mShip(nullptr)
,mPlayerDestroyAsteroid(0)
,mPlayerDestroyShip(0)
{
	
}

bool Game::Initialize(Renderer* renderer)
{
	mRenderer = renderer;

	mCollisionBroker = new CollisionBroker();
	
	return true;
}

void Game::UpdateGame(float deltaTime)
{
	if (mGameState == GameState::EGameplay)
	{
		// Update all actors
		mUpdatingActors = true;
		for (auto actor : mActors)
		{
			actor->Update(deltaTime);
		}
		mUpdatingActors = false;

		mCollisionBroker->HandleCollision(this);

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
			if (actor->GetState() == Actor::State::EDead)
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
		if (ui->GetState() == UIScreen::UIState::EActive)
		{
			ui->Update(deltaTime);
		}
	}
	// Delete any UIScreens that are closed
	auto iter = mUIStack.begin();
	while (iter != mUIStack.end())
	{
		if ((*iter)->GetState() == UIScreen::UIState::EClosing)
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

void Game::AddEnemyShip(class EnemyShip* enemyShip)
{
	mEnemyShips.emplace_back(enemyShip);
}

void Game::RemoveEnemyShip(class EnemyShip* enemyShip)
{
	auto iter = std::find(mEnemyShips.begin(),
		mEnemyShips.end(), enemyShip);
	if (iter != mEnemyShips.end())
	{
		mEnemyShips.erase(iter);
	}
}

void Game::Shutdown()
{
	UnloadData();

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