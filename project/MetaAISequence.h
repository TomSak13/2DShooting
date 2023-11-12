// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
#pragma once

class MetaAISequence
{
public:
	MetaAISequence() {}
	virtual ~MetaAISequence();
	virtual void Enter(class Game* game);
	virtual bool Execute(float deltaTime, class Game* game);
	virtual void Exit(class Game* game);
private:
};

