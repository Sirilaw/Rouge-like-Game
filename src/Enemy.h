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
	QString imagepath; //存放敌人图片路径
	Game1* wdow;

	int type;
	int move_tactic; //移动策略(为0时向角色移动,为1时向固定方向移动)
	int dir; //direction(即向哪个固定方向移动; 1 上;2 下; 3 左; 4 右)

	int expr_contribute = 10; //被杀死时贡献的经验值

	int ex, ey;
	int atk_value;
	int hurt_radius; //远程攻击类怪物的伤害半径

	int cur_hp;
	int max_hp;
	int die; //0 or 1; 0为活，1为死;

	int speed; //speed of moving

public:

	friend class Game1;
	friend class Weapon;

	Enemy();
	~Enemy();
	
	virtual void draw(QPainter* painter) = 0;
	void move();
	//实现攻击和被攻击的函数
	void attacked(Character* cha);
	void attacked(Weapon* wea);
	void attack(Character* cha);
	bool contain(Character* cha);
	void dead();

	//得到基本属性的函数
	int getx();
	int gety();
	int getatk_v(); 
	int getcur_hp();
	int getspeed();
	int getmax_hp();
};
