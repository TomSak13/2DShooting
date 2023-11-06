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

#include "AsteroidCollision.h"

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

	mCollision = new AsteroidCollision(game, this);
	mGame = game;
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);

	mCollision->RemoveCollision(mGame);
	delete mCollision;
}

void Asteroid::UpdateActor(float deltaTime)
{
	if (IsOutFrame())
	{
		SetState(EDead);
	}

	return;
}