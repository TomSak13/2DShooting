// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "RushSequence.h"
#include "Asteroid.h"
#include "Random.h"
#include "MetaAI.h"

RushSequence::RushSequence()
{

}

RushSequence::~RushSequence()
{

}

void RushSequence::Enter(Game* game)
{
	
}

bool RushSequence::Execute(float deltaTime, Game* game)
{
	return true;
}

PLAYER_EMOTION_STATE RushSequence::Exit(Game* game)
{
	return PLAYER_EMOTION_STATE::RELAX;
}
