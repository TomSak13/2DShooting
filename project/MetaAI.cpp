// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi
// 
// All rights reserved.
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Actor.h"
#include "MetaAI.h"
#include "Game.h"
#include "Asteroid.h"
#include "Random.h"
#include <algorithm>

MetaAI::MetaAI()
	:mCreateAsteroidInterval(MAX_CREATE_ASTEROID_INTERVAL),
	mState(PLAYER_EMOTION_STATE::INCREASE_ENEMY),
	mCreateAsteroidIntervalStep(MAX_CREATE_ASTEROID_INTERVAL)
{
	
}

MetaAI::~MetaAI()
{

}

void MetaAI::Initialize()
{
}

void MetaAI::UpdateGenerateAsteroid(class Game* game)
{
	Asteroid* asteroid = new Asteroid(game);

	Vector2 randPos = Random::GetVector(Vector2(FIELD_WIDTH * -1, FIELD_LENGTH),
		Vector2(FIELD_WIDTH, FIELD_LENGTH));
	asteroid->SetPosition(randPos);
}

void MetaAI::IncreaseEnemy(float deltaTime, Game* game, int asteroidCount)
{
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
			UpdateGenerateAsteroid(game);

			if (mCreateAsteroidIntervalStep > MIN_CREATE_ASTEROID_INTERVAL) {
				mCreateAsteroidIntervalStep -= INCREASE_CREATE_ASTEROID_STEP;
			}

			mCreateAsteroidInterval = mCreateAsteroidIntervalStep;
		}
	}

	/* state check */
	if (mCreateAsteroidIntervalStep <= MIN_CREATE_ASTEROID_INTERVAL)
	{
		mState = PLAYER_EMOTION_STATE::RUSH;
	}
}

void MetaAI::Rush(float deltaTime, Game* game, int asteroidCount)
{
	/* create boss */

	/* create asteroid */

	/* state check */
	
}

void MetaAI::Relax(float deltaTime, Game* game, int asteroidCount)
{
	/* create asteroid */

	/* state check */
}

void MetaAI::Update(float deltaTime, Game* game)
{
	std::vector<class Asteroid*> asteroidList = game->GetAsteroids();

	switch (mState)
	{
	    case PLAYER_EMOTION_STATE::INCREASE_ENEMY:
			IncreaseEnemy(deltaTime, game, asteroidList.size());
		    break;
	    case PLAYER_EMOTION_STATE::RUSH:
			Rush(deltaTime, game, asteroidList.size());
			break;
	    case PLAYER_EMOTION_STATE::RELAX:
			break;
		default:
			break;
	}
}