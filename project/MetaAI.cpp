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

MetaAI::MetaAI(Game* game)
	:Actor(game)
	, mCreateAsteroidInterval(2.0f)
{
	
}

MetaAI::~MetaAI()
{

}

void MetaAI::Initialize()
{
}

void MetaAI::UpdateActor(float deltaTime)
{
	std::vector<class Asteroid*> asteroidList = GetGame()->GetAsteroids();

	/* create boss */
	if (GetGame()->GetPlayerDestroyAsteroid() > 0 && GetGame()->GetPlayerDestroyAsteroid() % 5 == 0  
		&& GetGame()->GetEnemyShip() == NULL)
	{
		GetGame()->CreateEnemyShip();
	}

	/* create asteroid */
	if (asteroidList.size() >= MaxAsteroidNum)
	{
		return;
	}

	mCreateAsteroidInterval -= deltaTime;
	if (mCreateAsteroidInterval > 0.0f)
	{
		return;
	}
	else
	{
		mCreateAsteroidInterval = 0.5f;
	}

	Asteroid* asteroid = new Asteroid(GetGame());

	Vector2 randPos = Random::GetVector(Vector2(FIELD_WIDTH * -1, FIELD_LENGTH),
		Vector2(FIELD_WIDTH, FIELD_LENGTH));
	asteroid->SetPosition(randPos);	
}