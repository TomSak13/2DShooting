// ----------------------------------------------------------------
// Copyright (C) 2023 Tomohiko Sakaguchi. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once


class Collision
{
public:
	Collision(class Game* game);
	~Collision();

	void Remove(class Game* game);

	virtual bool HandleCollision(class Game* game); /* �Փˏ��� */
private:
};
