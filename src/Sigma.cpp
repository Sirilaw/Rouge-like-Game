#include "Sigma.h"
#include "Game1.h"

const QSize Sigma::fixedSize(60, 60);


Sigma::Sigma(QPoint pos, Game1* game) {
	window = game;
	ex = pos.x();
	ey = pos.y();

	imagepath = ":/image/Sigma.jpg";

	cur_hp = 700; //cur_hp
	max_hp = 700;
	atk_value = 35 + window->player_atk_enhance;
	hurt_radius = 50 + window->player_hr_enhance;

	speed = 12 + window->player_speed_enhance;
}

void Sigma::draw(QPainter* painter) const {
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


Sigma::~Sigma()
{}


