#include "Ghost.h"

const QSize fixedSize(70, 70);

Ghost::Ghost(QPoint pos, Game1* window)
{
	type = 2; //��2�ֹ���(Զ�̹���)
	move_tactic = rand() % 2;
	if (move_tactic) {
		dir = rand() % 4 + 1;
	}

	wdow = window;
	ex = pos.x();
	ey = pos.y();

	cur_hp = 65; //Ѫ����ʼֵ����Ѫ��Ϊ65
	max_hp = 65;
	die = 0;

	atk_value = 20;
	hurt_radius = 60;

	speed = 6;

	imagepath = ":/image/ghost.jpg";
}

Ghost::~Ghost()
{}

void Ghost::draw(QPainter * painter)
{
	//���Ƚ��������ƶ�
	move();

	//Ȼ���ͼƬ������
	painter->save();
	painter->setPen(Qt::red);
	painter->setBrush(QBrush(QColor(0,0,0,0)));
	painter->drawEllipse(QPoint(ex, ey), hurt_radius, hurt_radius);
	painter->drawPixmap(ex - fixedSize.width() / 2, ey - fixedSize.height() / 2, fixedSize.width(), fixedSize.width(), imagepath);

	static const double bloodbarwd = fixedSize.width();
	QPoint topleft = QPoint(ex - fixedSize.width() / 2, ey - fixedSize.height() / 2);
	painter->setPen(Qt::black);
	painter->setBrush(Qt::green);
	QRect bloodbarrect(topleft, QSize(bloodbarwd, 5));
	painter->drawRect(bloodbarrect);
	painter->setBrush(Qt::red);
	QRect healthBarRect(topleft, QSize((double)cur_hp / max_hp * bloodbarwd, 5));
	painter->drawRect(healthBarRect);//������ǰѪ��Ѫ��
}



