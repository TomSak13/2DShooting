// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once

#include "Collision.h"
#include "Asteroid.h"

class AsteroidCollision : Collision
{
public:
	AsteroidCollision(class Game* game, Asteroid* asteroid);
	~AsteroidCollision();

	void RemoveCollision(class Game* game);

	bool HandleCollision(class Game* game) override; /* è’ìÀèàóù */
private:
	Asteroid* mCollideAsteroid;
};
