#include "Bullet.h"
#include "Character.h"
#include "Game1.h"

const QSize Bullet::fixedSize(30, 30);

Bullet::Bullet(Character* oer)
{
	ex = oer->getx();
	ey = oer->gety();
	cur_pos = QPoint(ex, ey);
	speed = 18 + oer->window->weapon_speed_enhance;
	x_sign = oer->getxdir();
	y_sign = oer->getydir();

	atk_value = 25 + oer->window->weapon_atk_enhance;
	hurt_radius = 20 + oer->window->weapon_hr_enhance;

	owner = oer;
	imagepath = ":/image/PotionRed.png";
}

Bullet::~Bullet()
{}

void Bullet::draw(QPainter* painter) const {
	painter->save();
	painter->drawPixmap(ex - fixedSize.width() / 2, ey - fixedSize.height() / 2, fixedSize.width(), fixedSize.height(), imagepath);
}