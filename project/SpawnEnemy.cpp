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
#include <vector>

SpawnEnemy::SpawnEnemy()
{
	
}

SpawnEnemy::~SpawnEnemy()
{

}

void SpawnEnemy::Initialize(Game* game)
{
	
}

void SpawnEnemy::AddRespawnPlace(Vector2* respawnPlace)
{
	if (RESPAWN_PLACES_MAX_SIZE <= mRespawnPlaces.size())
	{
		return; /* リスポーン箇所の最大値を超えたので追加しない */
	}

	mRespawnPlaces.emplace_back(respawnPlace);
}

void SpawnEnemy::AddRespawnPlace(std::vector<Vector2*>& respawnPlaces)
{
	if (respawnPlaces.size() <= 0) 
	{
		return;
	}
	if (RESPAWN_PLACES_MAX_SIZE <= (respawnPlaces.size() + mRespawnPlaces.size()))
	{
		return; /* リスポーン箇所の最大値を超えたので追加しない */
	}

	for (auto iter : respawnPlaces)
	{
		if (iter == NULL)
		{
			continue;
		}
		mRespawnPlaces.emplace_back(iter);
	}
}

void SpawnEnemy::RemoveRespawnPlace(Vector2* respawnPlace)
{
	auto iter = std::find(mRespawnPlaces.begin(), mRespawnPlaces.end(), respawnPlace);
	if (iter != mRespawnPlaces.end())
	{
		mRespawnPlaces.erase(iter);
	}
}

Vector2 SpawnEnemy::CalcNextRespawnPlace()
{
	if (mRespawnPlaces.size() <= 0)
	{
		return Vector2(0, FIELD_LENGTH);
	}

	int nextIndex = Random::GetIntRange(0, (mRespawnPlaces.size()-1));


	return *mRespawnPlaces[nextIndex];
}

void SpawnEnemy::SpawnAsteroid(Game* game)
{
	Asteroid* asteroid = new Asteroid(game);

	Vector2 RespawnPlace = CalcNextRespawnPlace();

	asteroid->SetPosition(RespawnPlace);
}

void SpawnEnemy::SpawnEnemyShip(Game* game)
{
	EnemyShip* enemyShip = new EnemyShip(game);

	Vector2 RespawnPlace = CalcNextRespawnPlace();

	enemyShip->SetPosition(RespawnPlace);
	enemyShip->SetRotation(Math::PiOver2 * -1);
}