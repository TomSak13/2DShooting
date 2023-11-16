// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
#pragma once

#include "MetaAISequence.h"

class IncreaseEnemySequence : public MetaAISequence
{
public:
	IncreaseEnemySequence();
	~IncreaseEnemySequence();

	void Enter(class Game* game) override;
	bool Execute(float deltaTime, class Game* game, class SpawnEnemy* spawnEnemy) override;
	PLAYER_EMOTION_STATE Exit(class Game* game) override;
private:
	bool IsSpawnTime(float deltaTime);
	void CalcNextSpawnTime();
	float mCreateAsteroidInterval;
	float mCreateAsteroidIntervalStep;
};

