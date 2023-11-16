// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include "IncreaseEnemySequence.h"
#include "Asteroid.h"
#include "Random.h"
#include "MetaAI.h"
#include "EnemyShip.h"
#include "SpawnEnemy.h"

IncreaseEnemySequence::IncreaseEnemySequence()
: mCreateAsteroidInterval(MAX_CREATE_ASTEROID_INTERVAL),
  mCreateAsteroidIntervalStep(MAX_CREATE_ASTEROID_INTERVAL)
{

}

IncreaseEnemySequence::~IncreaseEnemySequence()
{

}

void IncreaseEnemySequence::Enter(Game* game)
{
	mCreateAsteroidInterval = MAX_CREATE_ASTEROID_INTERVAL;
	mCreateAsteroidIntervalStep = MAX_CREATE_ASTEROID_INTERVAL;
}

bool IncreaseEnemySequence::Execute(float deltaTime, Game* game, SpawnEnemy* spawnEnemy)
{
	int asteroidCount = game->GetAsteroids().size();
	int enemyShipCount = game->GetEnemyShips().size();

	if (!IsSpawnTime(deltaTime)) {
		
		return false;
	}
	/* 生成間隔計算。間隔は段々と狭めていく */
	CalcNextSpawnTime();

	/* create boss */
	/* このフェーズでは敵は一機 */
	if (game->GetPlayerDestroyAsteroid() > 0 && game->GetPlayerDestroyAsteroid() % 5 == 0
		&& enemyShipCount < 1)
	{
		spawnEnemy->SpawnEnemyShip(game);
	}

	/* create asteroid */
	if (asteroidCount < MAX_ASTEROID_NUM)
	{
		
		spawnEnemy->SpawnAsteroid(game);
	}

	/* state check */
	if (mCreateAsteroidIntervalStep <= MIN_CREATE_ASTEROID_INTERVAL)
	{
		return true;
	}

	return false;
}

PLAYER_EMOTION_STATE IncreaseEnemySequence::Exit(Game* game)
{
	return PLAYER_EMOTION_STATE::RUSH;
}

bool IncreaseEnemySequence::IsSpawnTime(float deltaTime)
{
	mCreateAsteroidInterval -= deltaTime;
	if (mCreateAsteroidInterval <= 0.0f)
	{
		return true;
	}

	return false;
}


void IncreaseEnemySequence::CalcNextSpawnTime()
{
	if (mCreateAsteroidIntervalStep > MIN_CREATE_ASTEROID_INTERVAL) {
		mCreateAsteroidIntervalStep -= INCREASE_CREATE_ASTEROID_STEP;
	}

	mCreateAsteroidInterval = mCreateAsteroidIntervalStep;
}