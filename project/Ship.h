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
class Ship : public Actor
{
public:
	const int MaxHp = 3;

	Ship(class Game* game);
	Ship::~Ship();

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;

	class CircleComponent* GetCircle() { return mCircle; }
	int GetHp() { return mHp; }
	void ReceiveDamage(int damage);
private:
	float mLaserCooldown;

	class CircleComponent* mCircle;
	int mHp;
};