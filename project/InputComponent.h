// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	// Lower update order to update first
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;
	
	// Getters/setters for private variables
	float GetMaxForward() const { return mMaxMoveSpeed; }
	float GetMaxAngular() const { return mMaxAngularSpeed; }
	int GetForwardKey() const { return mForwardKey; }
	int GetBackKey() const { return mBackKey; }
	int GetClockwiseKey() const { return mClockwiseKey; }
	int GetCounterClockwiseKey() const { return mCounterClockwiseKey; }
	int GetRightKey() const { return mRightKey; }
	int GetLeftKey() const { return mLeftKey; }

	void SetMaxForwardSpeed(float speed) { mMaxMoveSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }
	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackKey(int key) { mBackKey = key; }
	void SetClockwiseKey(int key) { mClockwiseKey = key; }
	void SetCounterClockwiseKey(int key) { mCounterClockwiseKey = key; }
	void SetRightKey(int key) { mRightKey = key; }
	void SetLeftKey(int key) { mLeftKey = key; }
private:
	// The maximum forward/angular speeds
	float mMaxMoveSpeed;
	float mMaxAngularSpeed;
	// Keys for forward/back movement
	int mForwardKey;
	int mBackKey;

	int mRightKey;
	int mLeftKey;

	// Keys for angular movement
	int mClockwiseKey;
	int mCounterClockwiseKey;
};
