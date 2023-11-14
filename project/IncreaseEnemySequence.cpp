// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "IncreaseEnemySequence.h"
#include "Asteroid.h"
#include "Random.h"
#include "MetaAI.h"
#include "EnemyShip.h"

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

bool IncreaseEnemySequence::Execute(float deltaTime, Game* game)
{
	int asteroidCount = game->GetAsteroids().size();
	int enemyShipCount = game->GetEnemyShips().size();

	/* create boss */
	/* このフェーズでは敵は一機 */
	if (game->GetPlayerDestroyAsteroid() > 0 && game->GetPlayerDestroyAsteroid() % 5 == 0
		&& enemyShipCount < 1)
	{
		EnemyShip* enemyShip = new EnemyShip(game);
		Vector2 randPos = Random::GetVector(Vector2(FIELD_WIDTH * -1, FIELD_LENGTH),
			Vector2(FIELD_WIDTH, FIELD_LENGTH));
		enemyShip->SetPosition(randPos);
		enemyShip->SetRotation(Math::PiOver2 * -1);
	}

	/* create asteroid */
	if (asteroidCount < MAX_ASTEROID_NUM)
	{
		/* 生成間隔を狭めながら増やしていく */
		mCreateAsteroidInterval -= deltaTime;
		if (mCreateAsteroidInterval <= 0.0f)
		{
			Asteroid* asteroid = new Asteroid(game);

			Vector2 randPos = Random::GetVector(Vector2(FIELD_WIDTH * -1, FIELD_LENGTH),
				Vector2(FIELD_WIDTH, FIELD_LENGTH));
			asteroid->SetPosition(randPos);

			if (mCreateAsteroidIntervalStep > MIN_CREATE_ASTEROID_INTERVAL) {
				mCreateAsteroidIntervalStep -= INCREASE_CREATE_ASTEROID_STEP;
			}

			mCreateAsteroidInterval = mCreateAsteroidIntervalStep;
		}
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
