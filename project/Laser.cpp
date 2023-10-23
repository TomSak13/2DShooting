// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. 
// Copyright (C) 2023 Tomohiko Sakaguchi
// 
// All rights reserved.
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Laser.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "CircleComponent.h"
#include "Asteroid.h"
#include "Ship.h"
#include "EnemyShip.h"
#include "Renderer.h"

Laser::Laser(Game* game)
	:Actor(game)
	,mDeathTimer(1.0f)
{
	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetRenderer()->GetTexture("Assets/Laser.png"));

	// Create a move component, and set a forward speed
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.0f);

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.0f);
}

void Laser::UpdateActor(float deltaTime)
{
	// If we run out of time, laser is dead
	mDeathTimer -= deltaTime;
	if (mDeathTimer <= 0.0f || IsOutFrame())
	{
		SetState(EDead);
	}
	else
	{
		// Do we intersect with an asteroid?
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				// The first asteroid we intersect with,
				// set ourselves and the asteroid to dead
				if (GetTeam() == EPlayer)
				{
					SetState(EDead);
					ast->SetState(EDead);
					return;
				}
			}
		}

		class Ship* playerShip = GetGame()->GetPlayerShip();
		if (playerShip != NULL)
		{
			if (playerShip->GetState() != EDead && playerShip->GetTeam() != GetTeam())
			{
				if (Intersect(*mCircle, *(playerShip->GetCircle())))
				{
					SetState(EDead);

					playerShip->ReceiveDamage(1);
					if (playerShip->GetHp() <= 0)
					{
						
						playerShip->SetState(EDead);
					}
				}
			}
		}

		class EnemyShip* enemyShip = GetGame()->GetEnemyShip();
		if (enemyShip != NULL)
		{
			if (enemyShip->GetState() != EDead && enemyShip->GetTeam() != GetTeam())
			{
				if (Intersect(*mCircle, *(enemyShip->GetCircle())))
				{
					SetState(EDead);

					enemyShip->ReceiveDamage(50);
					if (enemyShip->GetHp() <= 0)
					{
						
						enemyShip->SetState(EDead);
					}
				}
			}
		}
	}
}
