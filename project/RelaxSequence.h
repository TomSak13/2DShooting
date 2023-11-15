// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
#pragma once

#include "Game.h"
#include "MetaAISequence.h"

class RelaxSequence : public MetaAISequence
{
public:
	RelaxSequence();
	~RelaxSequence();

	void Enter(Game* game) override;
	bool Execute(float deltaTime, Game* game) override;
	PLAYER_EMOTION_STATE Exit(Game* game) override;
private:
	int mMaxAsteroidNum;
	float mCreateAsteroidInterval;
};

