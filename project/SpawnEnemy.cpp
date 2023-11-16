// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi
// 
// All rights reserved.
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Actor.h"
#include "SpawnEnemy.h"
#include "Game.h"
#include "Asteroid.h"
#include "Random.h"
#include "EnemyShip.h"
#include <algorithm>


SpawnEnemy::SpawnEnemy()
	
{
	
}

SpawnEnemy::~SpawnEnemy()
{

}

void SpawnEnemy::Initialize(Game* game)
{
	
}

void SpawnEnemy::SpawnAsteroid(Game* game)
{
	Asteroid* asteroid = new Asteroid(game);

	Vector2 randPos = Random::GetVector(Vector2(FIELD_WIDTH * -1, FIELD_LENGTH),
		Vector2(FIELD_WIDTH, FIELD_LENGTH));
	asteroid->SetPosition(randPos);
}

void SpawnEnemy::SpawnEnemyShip(Game* game)
{
	EnemyShip* enemyShip = new EnemyShip(game);
	Vector2 randPos = Random::GetVector(Vector2(FIELD_WIDTH * -1, FIELD_LENGTH),
		Vector2(FIELD_WIDTH, FIELD_LENGTH));
	enemyShip->SetPosition(randPos);
	enemyShip->SetRotation(Math::PiOver2 * -1);
}