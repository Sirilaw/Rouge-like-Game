#pragma once

#include "Enemy.h"

class Ghost  : public Enemy
{
	Q_OBJECT

public:
	friend class Game1;
	friend class Character;

	Ghost(QPoint pos, Game1* window);
	~Ghost();
	void draw(QPainter* painter);
};

