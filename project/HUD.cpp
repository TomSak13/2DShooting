// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "HUD.h"
#include "Texture.h"
#include "Shader.h"
#include "Game.h"
#include "Renderer.h"
#include "Ship.h"
#include <algorithm>

HUD::HUD(Game* game)
	:UIScreen(game)
{
	Renderer* r = mGame->GetRenderer();
	
	mHpTex = r->GetTexture("Assets/Blip.png");
}

HUD::~HUD()
{
}

void HUD::Update(float deltaTime)
{
	UIScreen::Update(deltaTime);
	
	int playerHp = 0;
	
	if (mGame->GetPlayerShip() != NULL)
	{
		playerHp = mGame->GetPlayerShip()->GetHp();
	}

	mHp.clear();
	for (int i = 0; i < playerHp; i++)
	{
		Vector2 hpMarkerPos(static_cast<float>(-500 + (i+1)*50), 350);
		mHp.push_back(hpMarkerPos);
	}
}

void HUD::Draw(Shader* shader)
{
	// Blips
	for (Vector2& blip : mHp)
	{
		DrawTexture(shader, mHpTex, blip, 1.0f);
	}
}


