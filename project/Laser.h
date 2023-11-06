// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. 
// Copyright (C) 2023 Tomohiko Sakaguchi
// 
// All rights reserved.
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"
class Laser : public Actor
{
public:
	Laser(class Game* game);
	~Laser();

	class CircleComponent* GetCircle() { return mCircle; }

	void UpdateActor(float deltaTime) override;

private:
	class CircleComponent* mCircle;
	class Game* mGame;
	class LaserCollision* mCollision;

	float mDeathTimer;
};
