#include "Weapon.h"
#include "Character.h"
#include "Game1.h"
#include "Enemy.h"

Weapon::Weapon() { ; }

Weapon::Weapon(QObject *parent)
	: QObject(parent)
{}

Weapon::~Weapon()
{}

void Weapon::move()
{
	ex += x_sign * speed;
	ey += y_sign * speed;
}

void Weapon::hittarget()
{
	int deltax = 0, deltay = 0;
	double distance = 0;
	int is_atk = 0;
	for (auto it = owner->window->enemy_vec.begin(); it != owner->window->enemy_vec.end();) {
		deltax = abs((*it)->getx() - ex);
		deltay = abs((*it)->gety() - ey);
		distance = sqrt(deltax * deltax + deltay * deltay);
		if (distance <= hurt_radius) {
			(*it)->attacked(this);
			it++;
		}
		else {
			it++;
		}
	}
}

int Weapon::getatk_v()
{
	return atk_value;
}

int Weapon::getx()
{
	return ex;
}

int Weapon::gety()
{
	return ey;
}


