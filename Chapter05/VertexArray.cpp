// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(const float* verts, unsigned int numVerts,
	const unsigned int* indices, unsigned int numIndices)
	:mNumVerts(numVerts)
	,mNumIndices(numIndices)
{
	// Create vertex array
	glGenVertexArrays(1, &mVertexArray); /* mVertexArray:���_�z��ID */
	glBindVertexArray(mVertexArray); /* ���_�z��I�u�W�F�N�g�쐬 */

	// Create vertex buffer
	glGenBuffers(1, &mVertexBuffer); /* mVertexBuffer:���_�o�b�t�@ID */
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer); /* ���_�o�b�t�@�I�u�W�F�N�g�쐬 */
	// ���_�o�b�t�@�ɁA�����Ŏw�肳�ꂽ���_�f�[�^verts���R�s�[�BUV����������邽�߁A�v�f��5
	glBufferData(GL_ARRAY_BUFFER,  // �o�b�t�@��� 
		numVerts * 5 * sizeof(float),  // �T�C�Y
		verts,                         // �R�s�[��
		GL_STATIC_DRAW);               // �f�[�^���p���@

	// Create index buffer(���_�o�b�t�@�Ɠ��l�̏���)
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// Specify the vertex attributes
	// (For now, assume one vertex format)
	// Position is 3 floats starting at offset 0
	
	// (x,y,z)�����Ɋւ��Đݒ�
	glEnableVertexAttribArray(0); /* ���_�����̗L���� */
	glVertexAttribPointer(
		0,                  // x,y,z������I��
		3,                  // x,y,z����
		GL_FLOAT,           // �v�f�̌^
		GL_FALSE,           // �����^�݂̂��g�p
		sizeof(float) * 5,  // ���_���W��(x,y,z,u,v)�̂���float 5���B�����͑S�̂̃T�C�Y
		0);

	// (u,v)�����Ɋւ��Đݒ�
	glEnableVertexAttribArray(1); // UV�����Ȃ̂�1�ɐݒ�
	glVertexAttribPointer(
		1,                  // UV����
		2,                  // u,v�Ȃ̂�2
		GL_FLOAT,           // �v�f�̌^
		GL_FALSE,           // �����^�݂̂��g�p
		sizeof(float) * 5,  // ���_���W��(x,y,z,u,v)�̂���float 5���B�����͑S�̂̃T�C�Y
		reinterpret_cast<void*>(sizeof(float) * 3)); // �I�t�Z�b�g�w��B(x,y,z)���擪�ɂ���̂ł������΂�
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);
}
