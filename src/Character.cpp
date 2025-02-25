#include "Character.h"
#include "Enemy.h"
#include "Game1.h"

Character::Character() { ; }

Character::Character(QObject *parent)
	: QObject(parent)
{}


Character::~Character()
{}

void Character::attacked(Enemy * enemy)
{
	cur_hp -= enemy->getatk_v();
	if (cur_hp <= 0) {
		window->cur_state = 3;
	}
}

void Character::attack(Enemy* enemy)
{
	enemy->attacked(this);
}

bool Character::contain(Enemy* ene)
{
	int deltax = abs(ex - ene->getx());
	int deltay = abs(ey - ene->gety());
	double distance = sqrt(deltax * deltax + deltay * deltay);
	if (distance <= hurt_radius) {
		return true;
	}
	return false;
}

void Character::promote(int n)
{
	cur_experience += n;
	if (cur_experience >= 100) {
		cur_level += 1;
		cur_experience = 0;
		window->cur_state = 2;
	}
}

int Character::getx()
{
	return ex;
}

int Character::gety()
{
	return ey;
}

int Character::getcur_hp()
{
	return cur_hp;
}

int Character::getmax_hp()
{
	return max_hp;
}

int Character::getatk_v()
{
	return atk_value;
}

int Character::getspeed()
{
	return speed;
}

int Character::getxdir()
{
	return x_dir;
}

int Character::getydir()
{
	return y_dir;
}
