// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. 
// Copyright (C) 2023 Tomohiko Sakaguchi
// 
// All rights reserved.
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
:Component(owner, updateOrder)
,mAngularSpeed(0.0f)
,mForwardSpeed(0.0f)
, mBesideSpeed(0.0f)
{
	
}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed))
	{
		float rot = mOwner->GetRotation();
		rot += mAngularSpeed * deltaTime;
		mOwner->SetRotation(rot);
	}
	
	if (!Math::NearZero(mForwardSpeed) || !Math::NearZero(mBesideSpeed))
	{
		Vector2 pos = mOwner->GetPosition();
		if (mBesideSpeed == 0)
		{
			pos += mOwner->GetForward() * mForwardSpeed * deltaTime; /// ‰ñ“]‚ ‚è
		}
		else
		{
			pos += Vector2(mBesideSpeed, mForwardSpeed) * deltaTime;
		}

		// Screen wrapping (for asteroids)
		if (pos.x < -512.0f) { pos.x = -512.0f; }
		else if (pos.x > 512.0f) { pos.x = 512.0f; }
		if (pos.y < -384.0f) { pos.y = -384.0f; }
		else if (pos.y > 384.0f) { pos.y = 384.0f; }

		mOwner->SetPosition(pos);
	}
}
