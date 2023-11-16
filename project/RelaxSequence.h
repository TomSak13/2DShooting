// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
#pragma once

#include "MetaAISequence.h"

class RelaxSequence : public MetaAISequence
{
public:
	RelaxSequence();
	~RelaxSequence();

	void Enter(class Game* game) override;
	bool Execute(float deltaTime, class Game* game, class SpawnEnemy* spawnEnemy) override;
	PLAYER_EMOTION_STATE Exit(class Game* game) override;
private:
	bool IsSpawnTime(float deltaTime);
	void CalcNextSpawnTime();
	int mMaxAsteroidNum;
	float mCreateAsteroidInterval;
};

