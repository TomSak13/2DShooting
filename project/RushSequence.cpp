// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include "RushSequence.h"
#include "SpawnEnemy.h"
#include "Asteroid.h"
#include "Random.h"
#include "MetaAI.h"

#include "EnemyShip.h"

RushSequence::RushSequence()
	: mCreateInterval(0)
{

}

RushSequence::~RushSequence()
{

}

void RushSequence::Enter(Game* game)
{
	mCreateInterval = MAX_CREATE_ASTEROID_INTERVAL / 2;
}

bool RushSequence::Execute(float deltaTime, Game* game, SpawnEnemy* spawnEnemy)
{
	int asteroidCount = game->GetAsteroids().size();
	int enemyShipCount = game->GetEnemyShips().size();

	/* 生成は0.5秒間隔で固定 */
	if (!IsSpawnTime(deltaTime))
	{
		return false;
	}
	mCreateInterval = MAX_CREATE_ASTEROID_INTERVAL / 2;


	/* create boss */
	if (game->GetPlayerDestroyAsteroid() > 0 && game->GetPlayerDestroyAsteroid() % 5 == 0
		&& enemyShipCount <= MAX_ENEMY_SHIP_NUM)
	{
		spawnEnemy->SpawnEnemyShip(game);
	}

	/* create asteroid */
	if (asteroidCount < MAX_ASTEROID_NUM)
	{
		spawnEnemy->SpawnAsteroid(game);
	}

	/* state check */
	if (game->GetPlayerDestroyShip() > DESTROY_ENEMY_COUNT_CHANGE_STATE)
	{
		/* ボスを決められた数破壊したらラッシュ修了 */
		return true;
	}

	return false;
}

PLAYER_EMOTION_STATE RushSequence::Exit(Game* game)
{
	return PLAYER_EMOTION_STATE::RELAX;
}

bool RushSequence::IsSpawnTime(float deltaTime)
{
	mCreateInterval -= deltaTime;
	if (mCreateInterval <= 0)
	{
		return true;
	}

	return false;
}