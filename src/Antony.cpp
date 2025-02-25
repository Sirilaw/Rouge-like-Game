#include "Antony.h"
#include <qmovie.h>

const QSize Antony::fixedSize(60,60);


Antony::Antony(QPoint pos, Game1* game) {
	window = game;
	ex = pos.x();
	ey = pos.y();
	imagepath = ":/image/Antonio.jpg";
	movie = new QMovie(imagepath);
	movie->start();
	startTimer(20);
	cur_hp = 10;
	max_hp = 500;
	atk_value = 25 + window->player_atk_enhance;
	hurt_radius = 30 + window->player_hr_enhance;
	speed = 10 + window->player_speed_enhance;
}

void Antony::draw(QPainter* painter) const {
	painter->save();
	painter->drawPixmap(ex - fixedSize.width() / 2, ey - fixedSize.height() / 2, fixedSize.width(), fixedSize.width(), movie->currentPixmap());

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
Antony::~Antony()
{}
