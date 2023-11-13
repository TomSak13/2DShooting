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

MetaAI::MetaAI()
	:mCreateAsteroidInterval(MAX_CREATE_ASTEROID_INTERVAL),
	mState(PLAYER_EMOTION_STATE::INCREASE_ENEMY),
	mCreateAsteroidIntervalStep(MAX_CREATE_ASTEROID_INTERVAL),
	mSequence(nullptr)
{
	
}

MetaAI::~MetaAI()
{

}

void MetaAI::Initialize(Game* game)
{
	mSequence = new IncreaseEnemySequence();
	mSequence->Enter(game);
}

void MetaAI::Update(float deltaTime, Game* game)
{
	if (mSequence == nullptr)
	{
		return;
	}

	if (mSequence->Execute(deltaTime, game))
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
			// ‚±‚±‚É—ˆ‚é‚±‚Æ‚Í‚È‚¢
			break;
		}

		if (mSequence != nullptr)
		{
			mSequence->Enter(game);
		}
	}
}