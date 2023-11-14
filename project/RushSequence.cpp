// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "RushSequence.h"
#include "Asteroid.h"
#include "Random.h"
#include "MetaAI.h"

#include "EnemyShip.h"

RushSequence::RushSequence()
{

}

RushSequence::~RushSequence()
{

}

void RushSequence::Enter(Game* game)
{
	
}

bool RushSequence::Execute(float deltaTime, Game* game)
{
	int asteroidCount = game->GetAsteroids().size();
	int enemyShipCount = game->GetEnemyShips().size();

	/* ƒ{ƒX‚ðŒÜ‘Ì”j‰ó‚µ‚½‚çƒ‰ƒbƒVƒ…C—¹ */
	if (game->GetPlayerDestroyShip() > 5)
	{
		return true;
	}

	/* create boss */
	if (game->GetPlayerDestroyAsteroid() > 0 && game->GetPlayerDestroyAsteroid() % 5 == 0
		&& enemyShipCount <= MAX_ENEMY_SHIP_NUM)
	{
		EnemyShip* enemyShip = new EnemyShip(game);
		Vector2 randPos = Random::GetVector(Vector2(FIELD_WIDTH * -1, FIELD_LENGTH),
			Vector2(FIELD_WIDTH, FIELD_LENGTH));
		enemyShip->SetPosition(randPos);
		enemyShip->SetRotation(Math::PiOver2 * -1);
	}

	/* create asteroid */
	if (asteroidCount < MAX_ASTEROID_NUM)
	{
		Asteroid* asteroid = new Asteroid(game);

		Vector2 randPos = Random::GetVector(Vector2(FIELD_WIDTH * -1, FIELD_LENGTH),
			Vector2(FIELD_WIDTH, FIELD_LENGTH));
		asteroid->SetPosition(randPos);
	}

	return false;
}

PLAYER_EMOTION_STATE RushSequence::Exit(Game* game)
{
	return PLAYER_EMOTION_STATE::RELAX;
}
