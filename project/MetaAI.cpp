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
	:mCreateAsteroidInterval(2.0f)
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

void MetaAI::Update(float deltaTime, Game* game)
{
	std::vector<class Asteroid*> asteroidList = game->GetAsteroids();

	/* create boss */
	if (game->GetPlayerDestroyAsteroid() > 0 && game->GetPlayerDestroyAsteroid() % 5 == 0
		&& game->GetEnemyShip() == NULL)
	{
		game->CreateEnemyShip();
	}

	/* create asteroid */
	if ((int)asteroidList.size() < MaxAsteroidNum)
	{
		/* 0.5•b‚²‚Æ‚Éˆê‚Â¶¬ */
		mCreateAsteroidInterval -= deltaTime;
		if (mCreateAsteroidInterval <= 0.0f)
		{
			UpdateGenerateAsteroid(game);
			mCreateAsteroidInterval = 0.5f;
		}
	}
}