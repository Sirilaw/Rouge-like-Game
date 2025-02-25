#include "Enemy.h"
#include "Character.h"
#include <cmath>
#include "Game1.h"
#include "Weapon.h"

Enemy::Enemy() {}
Enemy::~Enemy()
{}
void Enemy::move()
{
	if (!move_tactic) {
		//求出player的当前x坐标和y坐标
		int px = wdow->player->getx();
		int py = wdow->player->gety();
		int deltax = abs((px - ex));
		int deltay = abs((py - ey));
		double distance = sqrt(deltax * deltax + deltay * deltay);

		//坐标进行移动(注意方向:向左/向右 向上/向下)
		if (px >= ex) {
			ex += speed * deltax / distance;
			if (ex >= 1175) ex = 1175;
		}
		else {
			ex -= speed * deltax / distance;
			if (ex <= 25) ex = 25;
		}
		if (py >= ey) {
			ey += speed * deltay / distance;
			if (ey >= 775) ey = 775;
		}
		else {
			ey -= speed * deltay / distance;
			if (ey <= 25) ey = 25;
		}
	}
	else {
		switch (dir) {
		case 1: {
			ey -= speed;
			if (ey <= 25) {
				ey = 25;
				dir = 2;
			}
			break;
		}
		case 2: {
			ey += speed;
			if (ey >= 775) {
				ey = 775;
				dir = 1;
			}
			break;
		}
		case 3: {
			ex -= speed;
			if (ex <= 25) {
				ex = 25;
				dir = 4;
			}
			break;
		}
		case 4: {
			ex += speed;
			if (ex >= 1175) {
				ex = 1175;
				dir = 3;
			}
			break;
		}
		}
	}
}
void Enemy::attacked(Character* cha)
{
	cur_hp -= cha->getatk_v();
	if (cur_hp <= 0) {
		dead();
		cha->promote(expr_contribute);
	}
}
void Enemy::attacked(Weapon* wea)
{
	cur_hp -= wea->getatk_v();
	if (cur_hp <= 0) {
		dead();
		wea->owner->promote(expr_contribute);
	}
}
void Enemy::attack(Character* cha)
{
	if (contain(cha)) {
		cha->attacked(this);
	}
}
bool Enemy::contain(Character* cha)
{
	int deltax = abs(ex - cha->getx());
	int deltay = abs(ey - cha->gety());
	double distance = sqrt(deltax * deltax + deltay * deltay);
	if (distance <= hurt_radius) {
		return true;
	}
	return false;
}
void Enemy::dead()
{
	die = 1;
	wdow->killed_num += 1;
}
int Enemy::getx()
{
	return ex;
}
int Enemy::gety()
{
	return ey;
}
int Enemy::getatk_v()
{
	return atk_value;
}
int Enemy::getcur_hp()
{
	return cur_hp;
}
int Enemy::getspeed()
{
	return speed;
}
int Enemy::getmax_hp()
{
	return max_hp;
}
