// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once

#include "Collision.h"

class AsteroidCollision : public Collision
{
public:
	AsteroidCollision(class Game* game, class Asteroid* asteroid);
	~AsteroidCollision();

	void RemoveCollision(class Game* game);

	bool HandleCollision(class Game* game) override; /* è’ìÀèàóù */
private:
	class Asteroid* mCollideAsteroid;
};
