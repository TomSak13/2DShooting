// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Request GLSL 3.3
#version 330

// // グローバル変数(ワールド変換)。uniformは何度実行されても値が変わらない
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

// Attribute 0 is position, 1 is tex coords.
// layoutでどの属性がどの変数に対応するか設定する
// 0は頂点の座標
layout(location = 0) in vec3 inPosition;
// 1はテクスチャ座標。
layout(location = 1) in vec2 inTexCoord;

// フラグメントシェーダーへ出力される変数(フラグメントシェーダーが色の設定にテクスチャ座標も使うのでテクスチャ座標を返す)
out vec2 fragTexCoord;

void main()
{
	// 位置座標を同次座標系に変換(平行移動を実現するため)
	vec4 pos = vec4(inPosition, 1.0);
	// ワールド行列とビュー射影行列で座標変換
	gl_Position = pos * uWorldTransform * uViewProj;

	// Transform
	// Pass along the texture coordinate to frag shader
	fragTexCoord = inTexCoord;
}
