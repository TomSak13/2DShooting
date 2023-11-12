// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
#include "Game.h"
#include "MetaAI.h"

#pragma once
class MetaAISequence
{
public:
	virtual void Enter(Game* game);
	virtual MetaAI::PLAYER_EMOTION_STATE Execute(float deltaTime, Game* game);
	virtual void Exit(Game* game);
private:
};

