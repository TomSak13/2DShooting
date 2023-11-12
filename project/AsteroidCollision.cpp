// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
#include "AsteroidCollision.h"

#include "CircleComponent.h"
#include "Asteroid.h"
#include "Ship.h"
#include "EnemyShip.h"
#include "Actor.h"

#include "Game.h"

#include "Collision.h"

AsteroidCollision::AsteroidCollision(Game* game, Asteroid* asteroid) : Collision(game)
{
	mCollideAsteroid = asteroid;
}

AsteroidCollision::~AsteroidCollision()
{
	
}

void AsteroidCollision::RemoveCollision(Game* game)
{
	Collision::Remove(game);
}

bool AsteroidCollision::HandleCollision(Game* game)
{
	if (mCollideAsteroid == NULL || game == NULL)
	{
		return true;
	}

	class Ship* playerShip = game->GetPlayerShip();
	if (playerShip != NULL)
	{
		if (playerShip->GetState() != Actor::State::EDead && playerShip->GetTeam() != mCollideAsteroid->GetTeam())
		{
			if (Intersect(*(mCollideAsteroid->GetCircle()), *(playerShip->GetCircle())))
			{
				mCollideAsteroid->SetState(Actor::State::EDead);

				playerShip->ReceiveDamage(1);
				if (playerShip->GetHp() <= 0)
				{
					playerShip->SetState(Actor::State::EDead);
				}

				return true;
			}
		}
	}

	return false;
}