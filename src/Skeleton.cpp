#include "Skeleton.h"
#include "Game1.h"
#include <cmath>

const QSize fixedSize(70, 70);


Skeleton::Skeleton(QPoint pos, Game1* window)
{
	type = 1; //第1种怪物
	move_tactic = rand() % 2;
	if (move_tactic) {
		dir = rand() % 4 + 1;
	}

	wdow = window;
	ex = pos.x();
	ey = pos.y();

	cur_hp = 50;
	max_hp = 50;
	die = 0;

	atk_value = 15;
	hurt_radius = 5;

	speed = 4;

	imagepath = ":/image/skeleton.jpg";
}

Skeleton::~Skeleton() {}

void Skeleton::draw(QPainter * painter) 
{
	//首先进行坐标移动
	move();

	//然后把图片画出来
	painter->save();
	painter->drawPixmap(ex - fixedSize.width() / 2, ey - fixedSize.height() / 2, fixedSize.width(), fixedSize.width(), imagepath);
	static const double bloodbarwd = fixedSize.width();
	QPoint topleft = QPoint(ex - fixedSize.width() / 2, ey - fixedSize.height() / 2);
	painter->setPen(Qt::black);
	painter->setBrush(Qt::green);
	QRect bloodbarrect(topleft, QSize(bloodbarwd, 5));
	painter->drawRect(bloodbarrect);
	painter->setBrush(Qt::red);
	QRect healthBarRect(topleft, QSize((double)cur_hp / max_hp * bloodbarwd, 5));
	painter->drawRect(healthBarRect);//画出当前血量血条
}

