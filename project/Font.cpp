// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Font.h"
#include "Texture.h"
#include <vector>
#include "Game.h"

Font::Font(class Game* game)
	:mGame(game)
{
	
}

Font::~Font()
{
	
}

bool Font::Load(const std::string& fileName)
{
	// �T�|�[�g����t�H���g�T�C�Y
	std::vector<int> fontSizes = {
		8, 9,
		10, 11, 12, 14, 16, 18,
		20, 22, 24, 26, 28,
		30, 32, 34, 36, 38,
		40, 42, 44, 46, 48,
		52, 56,
		60, 64, 68,
		72
	};
	// �T�|�[�g����t�H���g�T�C�Y�����ׂėL����
	for (auto& size : fontSizes)
	{
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);
		if (font == nullptr)
		{
			SDL_Log("Failed to load font %s in size %d", fileName.c_str(), size);
			continue;
			//return false;
		}
		mFontData.emplace(size, font);
	}
	return true;
}

void Font::Unload()
{
	for (auto& font : mFontData)
	{
		TTF_CloseFont(font.second);
	}
}

// ��������󂯎���āA�K�؂ȃT�C�Y�̃t�H���g���g���ăe�N�X�`�����쐬����
// ���t���[������Ăяo���̂ł͂Ȃ��A�����񂪕ς��^�C�~���O�ŌĂяo��
Texture* Font::RenderText(const std::string& text,
						  const Vector3& color /*= Color::White*/,
						  int pointSize /*= 24*/)
{
	Texture* texture = nullptr;
	
	// Convert to SDL_Color(�F�w��)
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x * 255);
	sdlColor.g = static_cast<Uint8>(color.y * 255);
	sdlColor.b = static_cast<Uint8>(color.z * 255);
	sdlColor.a = 255;
	
	// �����Ŏw�肵���t�H���g�T�C�Y�̃t�H���g��T��
	auto iter = mFontData.find(pointSize);
	if (iter != mFontData.end())
	{
		TTF_Font* font = iter->second;

		// Draw this to a surface (blended for alpha)
		SDL_Surface* surf = TTF_RenderUTF8_Blended(font, text.c_str(), sdlColor);
		if (surf != nullptr)
		{
			// Convert from surface to texture
			texture = new Texture();
			texture->CreateFromSurface(surf);
			SDL_FreeSurface(surf);
		}
	}
	else
	{
		SDL_Log("Point size %d is unsupported", pointSize);
	}
	
	return texture;
}
