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

/* í≤êÆçœÇ›ÉpÉâÉÅÅ[É^ */
#define MAX_ASTEROID_NUM (20)
#define MAX_ENEMY_SHIP_NUM  (5)
#define BORDER_ASTEROID_NUM (5)
#define MAX_CREATE_ASTEROID_INTERVAL (1.0f)
#define INCREASE_CREATE_ASTEROID_STEP (0.01f) 
#define MIN_CREATE_ASTEROID_INTERVAL (0.5f)

class MetaAI
{
public:

	MetaAI();
	MetaAI::~MetaAI();

	void Initialize(Game* game);

	void Update(float deltaTime, class Game* game);

private:
	void MetaAI::IncreaseEnemy(float deltaTime, Game* game, int asteroidCount);
	void MetaAI::Rush(float deltaTime, Game* game, int asteroidCount);
	void MetaAI::Relax(float deltaTime, Game* game, int asteroidCount);

	void UpdateGenerateAsteroid(class Game* game);
	float mCreateAsteroidInterval;
	float mCreateAsteroidIntervalStep;
	PLAYER_EMOTION_STATE mState;

	MetaAISequence* mSequence;
};
