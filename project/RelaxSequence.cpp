// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "RelaxSequence.h"
#include "Asteroid.h"
#include "Random.h"
#include "MetaAI.h"

RelaxSequence::RelaxSequence()
{

}

RelaxSequence::~RelaxSequence()
{

}

void RelaxSequence::Enter(Game* game)
{
	
}

bool RelaxSequence::Execute(float deltaTime, Game* game)
{
	return true;
}

PLAYER_EMOTION_STATE RelaxSequence::Exit(Game* game)
{
	return PLAYER_EMOTION_STATE::INCREASE_ENEMY;
}
