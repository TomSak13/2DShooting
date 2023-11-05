// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include "Collision.h"

class CollisionBroker
{
public:
	CollisionBroker();
	~CollisionBroker();

	void AddCollision(Collision* collision);

	void HandleCollision(Game* game);

private:
	std::vector<Collision*> mCollisionStack;
};
