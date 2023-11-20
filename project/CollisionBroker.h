// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>

class CollisionBroker
{
public:
	CollisionBroker();
	~CollisionBroker();

	void AddCollision(class Collision* collision);
	void RemoveCollision(class Collision* collision);

	void HandleCollision(class Game* game);

private:
	std::vector<Collision*> mCollisionStack;
};
