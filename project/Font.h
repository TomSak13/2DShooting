// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <string>
#include <unordered_map>
#include <SDL/SDL_ttf.h>
#include "Math.h"

class Font
{
public:
	Font();
	~Font();
	
	// フォントファイルのロード/アンロード
	bool Load(const std::string& fileName);
	void Unload();
	
	// 文字列をテクスチャに描画
	class Texture* RenderText(const std::string& textKey,
							  const Vector3& color = Color::White,
							  int pointSize = 30);
private:
	// ポイントサイズとフォントデータの連想配列
	std::unordered_map<int, TTF_Font*> mFontData;
};
