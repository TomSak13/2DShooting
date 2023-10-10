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

	void UpdateActor(float deltaTime) override;

	bool IsOutFrame();
private:
	class CircleComponent* mCircle;
	float mDeathTimer;
};
