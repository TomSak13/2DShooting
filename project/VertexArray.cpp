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
	glGenVertexArrays(1, &mVertexArray); /* mVertexArray:頂点配列ID */
	glBindVertexArray(mVertexArray); /* 頂点配列オブジェクト作成 */

	// Create vertex buffer
	glGenBuffers(1, &mVertexBuffer); /* mVertexBuffer:頂点バッファID */
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer); /* 頂点バッファオブジェクト作成 */
	// 頂点バッファに、引数で指定された頂点データvertsをコピー。UV成分が加わるため、要素は5
	glBufferData(GL_ARRAY_BUFFER,  // バッファ種類 
		numVerts * 5 * sizeof(float),  // サイズ
		verts,                         // コピー元
		GL_STATIC_DRAW);               // データ利用方法

	// Create index buffer(頂点バッファと同様の処理)
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// Specify the vertex attributes
	// (For now, assume one vertex format)
	// Position is 3 floats starting at offset 0
	
	// (x,y,z)成分に関して設定
	glEnableVertexAttribArray(0); /* 頂点属性の有効化 */
	glVertexAttribPointer(
		0,                  // x,y,z成分を選択
		3,                  // x,y,z成分
		GL_FLOAT,           // 要素の型
		GL_FALSE,           // 整数型のみを使用
		sizeof(float) * 5,  // 頂点座標は(x,y,z,u,v)のためfloat 5個分。ここは全体のサイズ
		0);

	// (u,v)成分に関して設定
	glEnableVertexAttribArray(1); // UV成分なので1に設定
	glVertexAttribPointer(
		1,                  // UV成分
		2,                  // u,vなので2
		GL_FLOAT,           // 要素の型
		GL_FALSE,           // 整数型のみを使用
		sizeof(float) * 5,  // 頂点座標は(x,y,z,u,v)のためfloat 5個分。ここは全体のサイズ
		reinterpret_cast<void*>(sizeof(float) * 3)); // オフセット指定。(x,y,z)が先頭にあるのでそこを飛ばす
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
