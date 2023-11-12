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



class MetaAI
{
public:

    #define MAX_ASTEROID_NUM (30)
    #define BORDER_ASTEROID_NUM (5)
    #define MAX_CREATE_ASTEROID_INTERVAL (2.0f)
    #define INCREASE_CREATE_ASTEROID_STEP (0.1f) 
    #define MIN_CREATE_ASTEROID_INTERVAL (0.1f)

	enum class PLAYER_EMOTION_STATE{
		INCREASE_ENEMY,
		RUSH,
		RELAX,
	};

	MetaAI();
	MetaAI::~MetaAI();

	void Initialize();

	void Update(float deltaTime, class Game* game);

private:
	void MetaAI::IncreaseEnemy(float deltaTime, Game* game, int asteroidCount);
	void MetaAI::Rush(float deltaTime, Game* game, int asteroidCount);
	void MetaAI::Relax(float deltaTime, Game* game, int asteroidCount);

	void UpdateGenerateAsteroid(class Game* game);
	float mCreateAsteroidInterval;
	float mCreateAsteroidIntervalStep;
	PLAYER_EMOTION_STATE mState;
};
