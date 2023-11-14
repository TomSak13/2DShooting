// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
#include "LaserCollision.h"

#include "CircleComponent.h"
#include "Asteroid.h"
#include "Ship.h"
#include "EnemyShip.h"
#include "Actor.h"

#include "Game.h"

#include "Collision.h"

LaserCollision::LaserCollision(Game* game, Laser* laser) : Collision(game)
{
	mCollideLaser = laser;
}

LaserCollision::~LaserCollision()
{
	
}

void LaserCollision::RemoveCollision(Game* game)
{
	Collision::Remove(game);
}

bool LaserCollision::HandleCollision(Game* game)
{
	if (mCollideLaser == NULL || game == NULL)
	{
		return true;
	}

	/* “G‚ÌLaser‚Íasteroid‚ÆÚG”»’è‚Í–³‚µ */
	if (mCollideLaser->GetTeam() == Actor::Team::EPlayer)
	{
		for (auto ast : game->GetAsteroids())
		{
			if (Intersect(*(mCollideLaser->GetCircle()), *(ast->GetCircle())))
			{
				// The first asteroid we intersect with,
				// set ourselves and the asteroid to dead
				game->IncrementPlayerDestroyAsteroid();
				mCollideLaser->SetState(Actor::State::EDead);
				ast->SetState(Actor::State::EDead);
				return true;
			}
		}
	}

	/* Šeship‚Æ‚ÌÚG”»’è */
	class Ship* playerShip = game->GetPlayerShip();
	if (playerShip != NULL)
	{
		if (playerShip->GetState() != Actor::State::EDead && playerShip->GetTeam() != mCollideLaser->GetTeam())
		{
			if (Intersect(*(mCollideLaser->GetCircle()), *(playerShip->GetCircle())))
			{
				mCollideLaser->SetState(Actor::State::EDead);

				playerShip->ReceiveDamage(1);
				if (playerShip->GetHp() <= 0)
				{
					playerShip->SetState(Actor::State::EDead);
				}

				return true;
			}
		}
	}

	for (auto enemyShip : game->GetEnemyShips())
	{
		if (enemyShip->GetState() != Actor::State::EDead && enemyShip->GetTeam() != mCollideLaser->GetTeam())
		{
			if (Intersect(*(mCollideLaser->GetCircle()), *(enemyShip->GetCircle())))
			{
				mCollideLaser->SetState(Actor::State::EDead);

				enemyShip->ReceiveDamage(50);
				if (enemyShip->GetHp() <= 0)
				{
					enemyShip->SetState(Actor::State::EDead);
				}

				return true;
			}
		}
	}

	return false;
}