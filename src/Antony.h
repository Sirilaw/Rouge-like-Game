#pragma once

#include "Character.h"
#include "Game1.h"
#include "Enemy.h"
#include <qstring.h>
#include <qpainter.h>
#include <qpoint.h>

class Antony: public Character
{
	Q_OBJECT
private:
	static const QSize fixedSize;
	QMovie* movie;

public:
	Antony(QPoint pos, Game1* game);
	~Antony();
	void draw(QPainter* painter) const;
};
