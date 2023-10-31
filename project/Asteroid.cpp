// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"
#include "Ship.h"
#include "Renderer.h"

Asteroid::Asteroid(Game* game)
	:Actor(game)
	,mCircle(nullptr)
{

	SetRotation(Math::PiOver2 * -1);

	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetRenderer()->GetTexture("Assets/Asteroid.png"));

	// Create a move component, and set a forward speed
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(35.0f);

	// Add to mAsteroids in game
	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}

void Asteroid::UpdateActor(float deltaTime)
{
	if (IsOutFrame())
	{
		SetState(EDead);
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
}