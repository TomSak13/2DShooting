// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. 
// Copyright (C) 2023 Tomohiko Sakaguchi
// 
// All rights reserved.
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Ship.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Game.h"
#include "Laser.h"
#include "CircleComponent.h"
#include "Renderer.h"

Ship::Ship(Game* game)
	:Actor(game)
	,mHp(MaxHp)
	,mLaserCooldown(0.0f)
	
{
	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetRenderer()->GetTexture("Assets/Ship.png"));

	// Create an input component and set keys/speed
	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_LEFT);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_RIGHT);

	ic->SetRightKey(SDL_SCANCODE_D);
	ic->SetLeftKey(SDL_SCANCODE_A);

	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxAngularSpeed(Math::TwoPi);

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);

	SetTeam(Team::EPlayer);
}

Ship::~Ship()
{
	GetGame()->SetPlayerShip(NULL);
}

void Ship::ReceiveDamage(int damage)
{
#if GAME_DEBUG_NO_DAMAGE_MODE != 1
	for (int i = 0; i < damage; i++)
	{
		mHp--;
	}

	if (mHp <= 0)
	{
		mHp = 0;
	}
#endif
}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;
}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
	{
		// Create a laser and set its position/rotation to mine
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());
		laser->SetTeam(GetTeam());

		// Reset laser cooldown (half second)
		mLaserCooldown = 0.5f;
	}
}
