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

/* �����ς݃p�����[�^ */
#define MAX_ASTEROID_NUM (20)
#define MAX_ENEMY_SHIP_NUM  (3)
#define BORDER_ASTEROID_NUM (5)
#define MAX_CREATE_ASTEROID_INTERVAL (1.0f)
#define INCREASE_CREATE_ASTEROID_STEP (0.01f) 
#define MIN_CREATE_ASTEROID_INTERVAL (0.5f)

#define INTERVAL_RESPAWN_POSITION (50)

class MetaAI
{
public:
	MetaAI();
	~MetaAI();

	void Initialize(class Game* game);

	void Update(float deltaTime, class Game* game);

private:
	PLAYER_EMOTION_STATE mState;
	
	MetaAISequence* mSequence;

	class SpawnEnemy* mSpawnEnemy;
};
