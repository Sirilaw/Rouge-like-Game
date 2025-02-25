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
	int x_sign, y_sign; //ȡֵΪ0 or 1 or -1

	int atk_value;
	int hurt_radius;//�����hurt_radiusӦ�þ���С,ʹ���価�����ֳ�ֻ��λ���侭����·���ϵĵ��˲Ż��յ��˺�

	int enhance_atk_value;
	int enhance_weapon_value;
	int enhance_hr_value;

	Character* owner;

	QString imagepath;
};

