#pragma once

#include <QObject>
#include <qstring.h>
#include <qpoint.h>
#include <qpainter.h>
#include <qpropertyanimation.h>

class Character;
class Game1;
class Enemy;

class Weapon  : public QObject
{
	Q_OBJECT

public:
	friend class Character;
	friend class Game1;
	friend class Enemy;

	Weapon();
	Weapon(QObject *parent);
	~Weapon();

private:
	void move();
	virtual void draw(QPainter* painter) const = 0;
	int getatk_v();
	int getx();
	int gety();

private slots:
	void hittarget();

protected:
	QPoint cur_pos;
	int ex, ey;
	int speed;
	int x_sign, y_sign; //取值为0 or 1 or -1

	int atk_value;
	int hurt_radius;//这里的hurt_radius应该尽量小,使得其尽量表现出只有位于其经过的路径上的敌人才会收到伤害

	int enhance_atk_value;
	int enhance_weapon_value;
	int enhance_hr_value;

	Character* owner;

	QString imagepath;
};

