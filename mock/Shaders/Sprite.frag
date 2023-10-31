// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Request GLSL 3.3
#version 330

// 頂点シェーダーのout変数と名前を合わせて定義
in vec2 fragTexCoord;

// カラーバッファへ出力される変数
out vec4 outColor;

// // グローバル変数(テクスチャサンプリング)。uniformは何度実行されても値が変わらない
uniform sampler2D uTexture;

void main()
{
	// テクスチャから色をサンプリング
	outColor = texture(uTexture, fragTexCoord);
}
