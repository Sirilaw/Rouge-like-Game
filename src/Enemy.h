#pragma once

#include <QObject>
#include <QString>
#include <qpainter.h>

class Character;
class Game1;
class Weapon;

class Enemy  : public QObject
{
	Q_OBJECT
protected:
	QString imagepath; //��ŵ���ͼƬ·��
	Game1* wdow;

	int type;
	int move_tactic; //�ƶ�����(Ϊ0ʱ���ɫ�ƶ�,Ϊ1ʱ��̶������ƶ�)
	int dir; //direction(�����ĸ��̶������ƶ�; 1 ��;2 ��; 3 ��; 4 ��)

	int expr_contribute = 10; //��ɱ��ʱ���׵ľ���ֵ

	int ex, ey;
	int atk_value;
	int hurt_radius; //Զ�̹����������˺��뾶

	int cur_hp;
	int max_hp;
	int die; //0 or 1; 0Ϊ�1Ϊ��;

	int speed; //speed of moving

public:

	friend class Game1;
	friend class Weapon;

	Enemy();
	~Enemy();
	
	virtual void draw(QPainter* painter) = 0;
	void move();
	//ʵ�ֹ����ͱ������ĺ���
	void attacked(Character* cha);
	void attacked(Weapon* wea);
	void attack(Character* cha);
	bool contain(Character* cha);
	void dead();

	//�õ��������Եĺ���
	int getx();
	int gety();
	int getatk_v(); 
	int getcur_hp();
	int getspeed();
	int getmax_hp();
};
