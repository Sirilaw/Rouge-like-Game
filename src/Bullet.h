#pragma once

#include "Weapon.h"
#include "Character.h"

class Bullet  : public Weapon
{
	Q_OBJECT
private:
	static const QSize fixedSize;

public:
	Bullet(Character* owner);
	~Bullet();
	void draw(QPainter* painter) const;
};
