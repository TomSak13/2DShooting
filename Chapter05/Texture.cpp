// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Texture.h"
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <SDL/SDL.h>

Texture::Texture()
:mTextureID(0)
,mWidth(0)
,mHeight(0)
{
	
}

Texture::~Texture()
{
	
}

bool Texture::Load(const std::string& fileName)
{
	int channels = 0;
	
	unsigned char* image = SOIL_load_image(
		fileName.c_str(),
		&mWidth, 
		&mHeight, 
		&channels,      // 画像ファイルで使用するチャンネル数が返る
		SOIL_LOAD_AUTO  // 画像ファイルの種類
	);
	
	if (image == nullptr)
	{
		SDL_Log("SOIL failed to load image %s: %s", fileName.c_str(), SOIL_last_result());
		return false;
	}
	
	int format = GL_RGB;
	if (channels == 4)
	{
		format = GL_RGBA; // チャンネルが4つなら、RGBAで表現されている。アルファ値も加える
	}
	
	glGenTextures(1, &mTextureID);            // テクスチャオブジェクト作成
	glBindTexture(GL_TEXTURE_2D, mTextureID); // テクスチャをアクティブにする
	
	glTexImage2D(
		GL_TEXTURE_2D,     // テクスチャターゲット(2Dで描画)
		0,                 // LoD(level of detail)今は0
		format,            // 描画するするカラーフォーマット(RGBAで)
		mWidth,            // テクスチャ幅(元データのまま描画)
		mHeight,           // テクスチャ高さ(元データのまま描画)
		0,                 // 境界値
		format,            // 入力画像のカラーフォーマット(RGBA⇒RGBAで描画)
		GL_UNSIGNED_BYTE,  // 入力データのビット深度
		image              // 描画画像データ
	);
	
	SOIL_free_image_data(image); // 描画データはここで開放
	
	// サンプリング時のバイリニアフィルタリングを有効化
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	return true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &mTextureID);
}

void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}
