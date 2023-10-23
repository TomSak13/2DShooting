// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi
// 
// All rights reserved.
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include "Math.h"
#include "Actor.h"
#include <cstdint>

class MetaAI : public Actor
{
public:
	const int MaxAsteroidNum = 20;

	MetaAI(Game* game);
	MetaAI::~MetaAI();

	void Initialize();

	void UpdateActor(float deltaTime) override;

private:
	int asteroidNum;
};
