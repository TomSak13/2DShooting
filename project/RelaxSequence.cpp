// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include "RelaxSequence.h"
#include "SpawnEnemy.h"
#include "Asteroid.h"
#include "Random.h"
#include "MetaAI.h"

RelaxSequence::RelaxSequence()
	: mMaxAsteroidNum(0),
	mCreateAsteroidInterval(0),
	mCreateAsteroidIntervalStep(0)
{

}

RelaxSequence::~RelaxSequence()
{

}

void RelaxSequence::Enter(Game* game)
{
	mMaxAsteroidNum = MAX_ASTEROID_NUM;
	mCreateAsteroidInterval = MAX_CREATE_ASTEROID_INTERVAL / 2;
	mCreateAsteroidIntervalStep = MAX_CREATE_ASTEROID_INTERVAL / 2;
}

bool RelaxSequence::Execute(float deltaTime, Game* game, SpawnEnemy* spawnEnemy)
{
	int asteroidCount = game->GetAsteroids().size();

	/* 生成間隔を伸ばしていく */
	if (!IsSpawnTime(deltaTime))
	{
		return false;
	}
	CalcNextSpawnTime();

	/* create asteroid */
	if (asteroidCount <= mMaxAsteroidNum)
	{
		spawnEnemy->SpawnAsteroid(game);
	}

	/* state check */
	if (mCreateAsteroidIntervalStep >= MAX_CREATE_ASTEROID_INTERVAL)
	{
		return true;
	}

	return false;
}

PLAYER_EMOTION_STATE RelaxSequence::Exit(Game* game)
{
	return PLAYER_EMOTION_STATE::INCREASE_ENEMY;
}

bool RelaxSequence::IsSpawnTime(float deltaTime)
{
	mCreateAsteroidInterval -= deltaTime;
	if (mCreateAsteroidInterval <= 0.0f)
	{
		return true;
	}

	return false;
}


void RelaxSequence::CalcNextSpawnTime()
{
	mCreateAsteroidInterval = mCreateAsteroidIntervalStep;
	mCreateAsteroidIntervalStep += INCREASE_CREATE_ASTEROID_STEP;

	if (mCreateAsteroidIntervalStep >= MAX_CREATE_ASTEROID_INTERVAL)
	{
		mCreateAsteroidIntervalStep = MAX_CREATE_ASTEROID_INTERVAL;
	}
}