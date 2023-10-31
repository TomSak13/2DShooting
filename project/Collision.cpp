// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
#include "Collision.h"

Collision::Collision(Game* game)
{
	mCallback = nullptr;
}

Collision::~Collision()
{
	
}

void Collision::HandleCollision(Game* game)
{
	if (mCallback != nullptr)
	{
		mCallback(game);
	}
}