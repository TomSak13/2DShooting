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

	/* create boss */
	if (game->GetPlayerDestroyAsteroid() > 0 && game->GetPlayerDestroyAsteroid() % 5 == 0
		&& game->GetEnemyShip() == NULL)
	{
		game->CreateEnemyShip();
	}

	/* create asteroid */
	if (asteroidCount < MAX_ASTEROID_NUM)
	{
		/* ¶¬ŠÔŠu‚ð‹·‚ß‚È‚ª‚ç‘‚â‚µ‚Ä‚¢‚­ */
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
