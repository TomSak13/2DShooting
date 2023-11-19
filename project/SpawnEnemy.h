// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi
// 
// All rights reserved.
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once

#include <vector>
#include "Math.h"
#include "Actor.h"
#include <cstdint>
#include "MetaAISequence.h"

#define RESPAWN_PLACES_MAX_SIZE   (30)

class SpawnEnemy
{
public:

	SpawnEnemy();
	~SpawnEnemy();

	void Initialize(class Game* game);

	void AddRespawnPlace(Vector2* respawnPlace);
	void AddRespawnPlace(std::vector<Vector2*>& respawnPlaces);

	void RemoveRespawnPlace(Vector2* respawnPlace);

	void SpawnAsteroid(class Game* game);
	void SpawnEnemyShip(class Game* game);

private:

	Vector2 CalcNextRespawnPlace();

	std::vector<Vector2*> mRespawnPlaces;
};
