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


class SpawnEnemy
{
public:

	SpawnEnemy();
	~SpawnEnemy();

	void Initialize(class Game* game);

	void SpawnAsteroid(class Game* game);
	void SpawnEnemyShip(class Game* game);

private:
	
};
