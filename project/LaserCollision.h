// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once

#include "Collision.h"
#include "Laser.h"

class LaserCollision : Collision
{
public:
	LaserCollision(class Game* game, Laser* laser);
	~LaserCollision();

	void RemoveCollision(class Game* game);

	bool HandleCollision(class Game* game) override; /* è’ìÀèàóù */
private:
	Laser* mCollideLaser;
};
