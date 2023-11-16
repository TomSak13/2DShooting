// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "MetaAISequence.h"
#include "Game.h"
#include "SpawnEnemy.h"

MetaAISequence::~MetaAISequence()
{

}

void MetaAISequence::Enter(Game* game)
{

}

bool MetaAISequence::Execute(float deltaTime, Game* game, SpawnEnemy* spawnEnemy)
{
	return true;
}

PLAYER_EMOTION_STATE MetaAISequence::Exit(Game* game)
{
	return PLAYER_EMOTION_STATE::INCREASE_ENEMY;
}