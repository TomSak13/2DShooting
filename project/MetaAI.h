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

class MetaAI
{
public:
	const int MaxAsteroidNum = 20;

	MetaAI();
	MetaAI::~MetaAI();

	void Initialize();

	void Update(float deltaTime, class Game* game);

private:

	void UpdateGenerateAsteroid(class Game* game);
	float mCreateAsteroidInterval;
};
