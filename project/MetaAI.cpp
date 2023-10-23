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
#include <algorithm>

MetaAI::MetaAI(Game* game)
	:Actor(game)
	, asteroidNum(0)
{
	
}

MetaAI::~MetaAI()
{

}

void MetaAI::Initialize()
{
	// Create asteroids
	asteroidNum = MaxAsteroidNum;
	for (int i = 0; i < asteroidNum; i++)
	{
		new Asteroid(GetGame());
	}
}

void MetaAI::UpdateActor(float deltaTime)
{
	
}
