// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
#pragma once

#include "Game.h"
#include "MetaAISequence.h"

class IncreaseEnemySequence : public MetaAISequence
{
public:
	IncreaseEnemySequence();
	~IncreaseEnemySequence();

	void Enter(Game* game) override;
	bool Execute(float deltaTime, Game* game) override;
	void Exit(Game* game) override;
private:
	float mCreateAsteroidInterval;
	float mCreateAsteroidIntervalStep;
};

