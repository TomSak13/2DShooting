// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
#include "Collision.h"
#include "CollisionBroker.h"
#include "Game.h"

Collision::Collision(Game* game)
{
	game->GetCollisionBroker()->AddCollision(this);
}

Collision::~Collision()
{
	
}

void Collision::Remove(Game* game)
{
	game->GetCollisionBroker()->RemoveCollision(this);
}

bool Collision::HandleCollision(Game* game)
{
	return true;
}