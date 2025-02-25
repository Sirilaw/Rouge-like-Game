#pragma once

#include "Enemy.h"
#include <qpainter.h>
#include "Game1.h"
#include "Character.h"

class Skeleton  : public Enemy
{
	Q_OBJECT

public:
	friend class Game1;
	friend class Character;

	Skeleton(QPoint pos, Game1* window);
	~Skeleton();   
	void draw(QPainter* painter);
};
