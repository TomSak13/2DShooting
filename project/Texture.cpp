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
		&channels,      // �摜�t�@�C���Ŏg�p����`�����l�������Ԃ�
		SOIL_LOAD_AUTO  // �摜�t�@�C���̎��
	);
	
	if (image == nullptr)
	{
		SDL_Log("SOIL failed to load image %s: %s", fileName.c_str(), SOIL_last_result());
		return false;
	}
	
	int format = GL_RGB;
	if (channels == 4)
	{
		format = GL_RGBA; // �`�����l����4�Ȃ�ARGBA�ŕ\������Ă���B�A���t�@�l��������
	}
	
	glGenTextures(1, &mTextureID);            // �e�N�X�`���I�u�W�F�N�g�쐬
	glBindTexture(GL_TEXTURE_2D, mTextureID); // �e�N�X�`�����A�N�e�B�u�ɂ���
	
	glTexImage2D(
		GL_TEXTURE_2D,     // �e�N�X�`���^�[�Q�b�g(2D�ŕ`��)
		0,                 // LoD(level of detail)����0
		format,            // �`�悷�邷��J���[�t�H�[�}�b�g(RGBA��)
		mWidth,            // �e�N�X�`����(���f�[�^�̂܂ܕ`��)
		mHeight,           // �e�N�X�`������(���f�[�^�̂܂ܕ`��)
		0,                 // ���E�l
		format,            // ���͉摜�̃J���[�t�H�[�}�b�g(RGBA��RGBA�ŕ`��)
		GL_UNSIGNED_BYTE,  // ���̓f�[�^�̃r�b�g�[�x
		image              // �`��摜�f�[�^
	);
	
	SOIL_free_image_data(image); // �`��f�[�^�͂����ŊJ��
	
	// �T���v�����O���̃o�C���j�A�t�B���^�����O��L����
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
