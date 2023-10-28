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
#include "Font.h"
#include <algorithm>

HUD::HUD(Game* game)
	:UIScreen(game)
{
	Renderer* r = mGame->GetRenderer();
	
	mHpTex = r->GetTexture("Assets/Blip.png");
	mHpText = mFont->RenderText("HP", Color::Red, 24);
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
		Vector2 hpMarkerPos(static_cast<float>(-475 + (i+1)*50), 350);
		mHp.push_back(hpMarkerPos);
	}

	char scoreText[64];
	int score = mGame->GetPlayerDestroyAsteroid() + (5 * mGame->GetPlayerDestroyShip());
	sprintf_s(scoreText, "SCORE    %04d",score);
	mScore = mFont->RenderText(scoreText, Color::White, 24);
}

void HUD::Draw(Shader* shader)
{
	// Blips
	DrawTexture(shader, mHpText, Vector2(-475.0f, 350.0f), 1.0f);
	if (mHpTex != NULL)
	{
		for (Vector2& blip : mHp)
		{
			DrawTexture(shader, mHpTex, blip, 1.0f);
		}
	}

	// Score
	if (mScore != NULL)
	{
		DrawTexture(shader, mScore, Vector2(350.0f,350.0f),1.0F);
	}
}


