// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. 
//               2023 Tomohiko Sakaguchi
// All rights reserved.
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "BGSpriteComponent.h"
#include "Texture.h"
#include "Actor.h"
#include "Shader.h"
#include "Renderer.h"

BGSpriteComponent::BGSpriteComponent(class Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	,mScrollSpeed(0.0f)
{
}

void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	for (auto& bg : mBGTextures)
	{
		// Update the x offset
		bg.mOffset.y += mScrollSpeed * deltaTime;
		// If this is completely off the screen, reset offset to
		// the right of the last bg texture
		if (bg.mOffset.y < -1.0f * bg.mTexture->GetHeight())
		{
			bg.mOffset.y = static_cast<float>((mBGTextures.size() - 1) * bg.mTexture->GetHeight() - 1);
		}
	}
}

void BGSpriteComponent::Draw(class Shader* shader)
{
	// Draw each background texture
	for (auto& bg : mBGTextures)
	{
		// Draw this background
			// Scale the quad by the width/height of texture
		Matrix4 scaleMat = Matrix4::CreateScale(
			static_cast<float>(bg.mTexture->GetWidth()),
			static_cast<float>(bg.mTexture->GetHeight()),
			1.0f);
		// Translate to position on screen
		Matrix4 transMat = Matrix4::CreateTranslation(
			Vector3(bg.mOffset.x, bg.mOffset.y, 0.0f));
		// Set world transform
		Matrix4 world = scaleMat * transMat;
		shader->SetMatrixUniform("uWorldTransform", world);
		// Set current texture
		bg.mTexture->SetActive();
		// Draw quad
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void BGSpriteComponent::SetBGTextures(const std::vector<Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures)
	{
		BGTexture temp;
		temp.mTexture = tex;
		// Each texture is screen width in offset
		temp.mOffset.x = 0;
		temp.mOffset.y = static_cast<float>(count * tex->GetHeight());
		mBGTextures.emplace_back(temp);
		count++;
	}
}
