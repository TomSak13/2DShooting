// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "MetaAISequence.h"

void MetaAISequence::Enter(Game* game) 
{

}

MetaAI::PLAYER_EMOTION_STATE MetaAISequence::Execute(float deltaTime, Game* game)
{
	return MetaAI::PLAYER_EMOTION_STATE::INCREASE_ENEMY;
}

void MetaAISequence::Exit(Game* game)
{

}
