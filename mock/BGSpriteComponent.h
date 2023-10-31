// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. 
//               2023 Tomohiko Sakaguchi
// All rights reserved.
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SpriteComponent.h"
#include <vector>
#include "Math.h"
class BGSpriteComponent : public SpriteComponent
{
public:
	// Set draw order to default to lower (so it's in the background)
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	// Update/draw overridden from parent
	void Update(float deltaTime) override;
	void Draw(class Shader* shader) override;
	// Set the textures used for the background
	void SetBGTextures(const std::vector<Texture*>& textures);
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }
private:
	// Struct to encapsulate each bg image and its offset
	struct BGTexture
	{
		Texture* mTexture;
		Vector2 mOffset;
	};
	std::vector<BGTexture> mBGTextures;
	float mScrollSpeed;
};
