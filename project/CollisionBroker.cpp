// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
#include "CollisionBroker.h"
#include "Collision.h"
#include "Game.h"

CollisionBroker::CollisionBroker()
{
	
}

CollisionBroker::~CollisionBroker()
{
	mCollisionStack.clear();
}

void CollisionBroker::RemoveCollision(Collision* collision)
{
	auto iter = std::find(mCollisionStack.begin(), mCollisionStack.end(), collision);
	if (iter != mCollisionStack.end())
	{
		mCollisionStack.erase(iter);
	}
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
		if (collision == NULL)
		{
			continue;
		}

		if (collision->HandleCollision(game))
		{
			RemoveCollision(collision);
		}
	}
}