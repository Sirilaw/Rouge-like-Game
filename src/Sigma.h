#pragma once

#include "Character.h"

class Sigma  : public Character
{
	Q_OBJECT

private:
	static const QSize fixedSize;

public:
	Sigma(QPoint pos, Game1* game);
	~Sigma();
	void draw(QPainter* painter) const;
};


