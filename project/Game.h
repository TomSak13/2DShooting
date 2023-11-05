// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. 
// Copyright (C) 2023 Tomohiko Sakaguchi
// 
// All rights reserved.
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SDL/SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

#define FIELD_WIDTH (512.0f)
#define FIELD_LENGTH (384.0f)

class Game
{
public:
	enum GameState
	{
		EStart,
		EGameplay,
		EPaused,
		EQuit,
	};

	Game();
	bool Initialize();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	class Renderer* GetRenderer() const { return mRenderer; }

	GameState GetState() const { return mGameState; }
	void SetState(GameState state) { mGameState = state; }

	// Game-specific (add/remove asteroid)
	void AddAsteroid(class Asteroid* ast);
	void RemoveAsteroid(class Asteroid* ast);
	std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }
	class Ship* GetPlayerShip() { return mShip; }
	class EnemyShip* GetEnemyShip() { return mEnemyShip; }
	void SetPlayerShip(class Ship* ship) { mShip = ship; }
	void CreateEnemyShip();
	void SetEnemyShip(class EnemyShip* enemyShip) { mEnemyShip = enemyShip; }

	const std::vector<class UIScreen*>& GetUIStack() { return mUIStack; }
	void PushUI(class UIScreen* screen);

	void IncrementPlayerDestroyAsteroid() { mPlayerDestroyAsteroid++; }
	int GetPlayerDestroyAsteroid() { return mPlayerDestroyAsteroid; }

	void IncrementPlayerDestroyShip() { mPlayerDestroyShip++; }
	int GetPlayerDestroyShip() { return mPlayerDestroyShip; }

	std::vector<class Actor*> GetActors() { return mActors; }
	std::vector<class Actor*> GetPendingActors() { return mPendingActors; }

	bool GetUpdatingActors() { return mUpdatingActors; }
	void SetUpdatingActors(bool updatingActors) { mUpdatingActors = updatingActors; }

	void UpdateGame();
	void GenerateOutput();
private:
	
	void LoadData();
	void UnloadData();
	void CreateBackGround();

	// All the actors in the game
	std::vector<class Actor*> mActors;
	// Any pending actors
	std::vector<class Actor*> mPendingActors;

	class Renderer* mRenderer;
	class HUD* mHUD;

	Uint32 mTicksCount;

	GameState mGameState;

	// Track if we're updating actors right now
	bool mUpdatingActors;

	// Game-specific
	class MetaAI* mMetaAI;
	class Ship* mShip; // Player's ship
	class EnemyShip* mEnemyShip;
	std::vector<class Asteroid*> mAsteroids;

	std::vector<class UIScreen*> mUIStack;

	int mPlayerDestroyAsteroid;
	int mPlayerDestroyShip;
};
