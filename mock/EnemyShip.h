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
class EnemyShip : public Actor
{
public:
	const int MaxHp = 100;

	EnemyShip(class Game* game);
	EnemyShip::~EnemyShip();

	void UpdateActor(float deltaTime) override;

	class CircleComponent* GetCircle() { return mCircle;}
	int GetHp() { return mHp; }
	void ReceiveDamage(int damage);
private:
	float mLaserCooldown;

	class CircleComponent* mCircle;
	int mHp;
};