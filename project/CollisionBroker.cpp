// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
#include "CollisionBroker.h"
#include "Game.h"

CollisionBroker::CollisionBroker()
{
	
}

CollisionBroker::~CollisionBroker()
{
	mCollisionStack.clear();
}

void CollisionBroker::AddCollision(Collision* collision)
{
	if (collision == NULL)
	{
		return;
	}

	mCollisionStack.emplace_back(collision);
}

void CollisionBroker::HandleCollision(Game* game)
{
	for (auto collision: mCollisionStack)
	{
		collision->HandleCollision(game);
	}

	mCollisionStack.clear();
}