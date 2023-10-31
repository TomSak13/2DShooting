// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once

typedef void (*handleCollisionCallback)(class Game* game);

class Collision
{
public:
	Collision(class Game* game);
	~Collision();

	void SetCallback(handleCollisionCallback callback) {mCallback = callback;}

	void HandleCollision(Game* game); /* è’ìÀèàóù */
private:
	handleCollisionCallback mCallback;
};
