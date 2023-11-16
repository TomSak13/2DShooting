// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
#pragma once

enum class PLAYER_EMOTION_STATE {
	INCREASE_ENEMY = 0,
	RUSH,
	RELAX,
};

class MetaAISequence
{
public:
	MetaAISequence() {}
	virtual ~MetaAISequence();
	virtual void Enter(class Game* game);
	virtual bool Execute(float deltaTime, class Game* game, class SpawnEnemy* spawnEnemy);
	virtual PLAYER_EMOTION_STATE Exit(class Game* game);
private:
};

