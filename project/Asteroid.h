// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"
class Asteroid : public Actor
{
public:
	Asteroid(class Game* game);
	~Asteroid();
	
	void Asteroid::UpdateActor(float deltaTime) override;
	class CircleComponent* GetCircle() { return mCircle; }
private:
	class Game* mGame;
	class AsteroidCollision* mCollision;
	class CircleComponent* mCircle;
};
