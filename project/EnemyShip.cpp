// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. 
// Copyright (C) 2023 Tomohiko Sakaguchi
// 
// All rights reserved.
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "EnemyShip.h"
#include "SpriteComponent.h"
#include "CircleComponent.h"
#include "InputComponent.h"
#include "Game.h"
#include "Laser.h"
#include "Renderer.h"

EnemyShip::EnemyShip(Game* game)
	:Actor(game)
	,mHp(MaxHp)
	,mLaserCooldown(0.0f)
{
	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetRenderer()->GetTexture("Assets/Ship.png"));

	// Create a move component
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(10.0f); // for debug

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);

	SetTeam(Team::EEnemy);
}

EnemyShip::~EnemyShip()
{
	GetGame()->SetEnemyShip(NULL);
	GetGame()->IncrementPlayerDestroyShip();
}

void EnemyShip::ReceiveDamage(int damage)
{
	mHp -= damage;
	if (mHp <= 0)
	{
		mHp = 0;
	}
}

void EnemyShip::UpdateActor(float deltaTime)
{
	if (mLaserCooldown <= 0.0f)
	{
		// Create a laser and set its position/rotation to mine
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());
		laser->SetTeam(GetTeam());

		// Reset laser cooldown (half second) レーザーのインターバル時間
		mLaserCooldown = 3.0f;
	}

	mLaserCooldown -= deltaTime;
}
