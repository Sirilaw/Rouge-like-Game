#pragma once

#include "Weapon.h"
#include "Character.h"

class Atkwing  : public Weapon
{
	Q_OBJECT
private:
	static const QSize fixedSize;

public:
	Atkwing(Character* owner);
	~Atkwing();
	void draw(QPainter* painter) const;
};
