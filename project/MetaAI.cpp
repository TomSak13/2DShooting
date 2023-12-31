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

#include "IncreaseEnemySequence.h"
#include "RushSequence.h"
#include "RelaxSequence.h"

#include "SpawnEnemy.h"

MetaAI::MetaAI()
	:mState(PLAYER_EMOTION_STATE::INCREASE_ENEMY),
	mSequence(nullptr),
	mSpawnEnemy(nullptr)
{
	
}

MetaAI::~MetaAI()
{

}

void MetaAI::Initialize(Game* game)
{
	mSpawnEnemy = new SpawnEnemy();
	mSpawnEnemy->Initialize(game);

	std::vector<Vector2*> respawnPos;
	for (float i = (-1 * FIELD_WIDTH); i < FIELD_WIDTH; i += INTERVAL_RESPAWN_POSITION)
	{
		Vector2* spawnPos = new Vector2(i, FIELD_LENGTH);
		respawnPos.push_back(spawnPos);
	}
	mSpawnEnemy->AddRespawnPlace(respawnPos);

	mSequence = new IncreaseEnemySequence();
	mSequence->Enter(game);
}

void MetaAI::Update(float deltaTime, Game* game)
{
	if (mSequence == nullptr)
	{
		return;
	}

	if (mSequence->Execute(deltaTime, game, mSpawnEnemy))
	{
		mState = mSequence->Exit(game);

		delete mSequence;
		mSequence = nullptr;

		switch (mState)
		{
		case PLAYER_EMOTION_STATE::INCREASE_ENEMY:
			mSequence = new IncreaseEnemySequence();
			break;
		case PLAYER_EMOTION_STATE::RUSH:
			mSequence = new RushSequence();
			break;
		case PLAYER_EMOTION_STATE::RELAX:
			mSequence = new RelaxSequence();
			break;
		default:
			// ここに来ることはない
			break;
		}

		if (mSequence != nullptr)
		{
			mSequence->Enter(game);
		}
	}
}