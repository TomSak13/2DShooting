// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "RelaxSequence.h"
#include "Asteroid.h"
#include "Random.h"
#include "MetaAI.h"

RelaxSequence::RelaxSequence()
	: mMaxAsteroidNum(0),
	mCreateAsteroidInterval(0)
{

}

RelaxSequence::~RelaxSequence()
{

}

void RelaxSequence::Enter(Game* game)
{
	mMaxAsteroidNum = MAX_ASTEROID_NUM;
	mCreateAsteroidInterval = MAX_CREATE_ASTEROID_INTERVAL / 2;
}

bool RelaxSequence::Execute(float deltaTime, Game* game)
{
	int asteroidCount = game->GetAsteroids().size();

	/* ¶¬ŠÔŠu‚ðL‚Î‚µ‚Ä‚¢‚­ */
	mCreateAsteroidInterval -= deltaTime;
	if (mCreateAsteroidInterval > 0)
	{
		return false;
	}
	else
	{
		mCreateAsteroidInterval += INCREASE_CREATE_ASTEROID_STEP;
		if (mCreateAsteroidInterval >= MAX_CREATE_ASTEROID_INTERVAL)
		{
			mCreateAsteroidInterval = MAX_CREATE_ASTEROID_INTERVAL;
		}
	}

	if (asteroidCount <= mMaxAsteroidNum)
	{
		Asteroid* asteroid = new Asteroid(game);

		Vector2 randPos = Random::GetVector(Vector2(FIELD_WIDTH * -1, FIELD_LENGTH),
			Vector2(FIELD_WIDTH, FIELD_LENGTH));
		asteroid->SetPosition(randPos);

		mMaxAsteroidNum--;
	}

	if (mMaxAsteroidNum <= BORDER_ASTEROID_NUM)
	{
		return true;
	}

	return false;
}

PLAYER_EMOTION_STATE RelaxSequence::Exit(Game* game)
{
	return PLAYER_EMOTION_STATE::INCREASE_ENEMY;
}
