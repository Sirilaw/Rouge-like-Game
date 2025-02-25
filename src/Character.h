#pragma once

#include <QObject>
#include <QString>
#include <qpainter.h>

class Enemy;
class Weapon;
class Game1;
class Atkwing;
class Bullet;

class Character  : public QObject
{
	Q_OBJECT
protected:
	QString imagepath; //记录角色图片所在路径

	Game1* window;

	int ex, ey; //位置坐标
	int cur_hp; //当前血量
	int max_hp; //最大血量

	int cur_experience = 0; //当前经验值
	int cur_level = 1; //当前等级
	
	int weapon; //武器
	int atk_value; //基础攻击值
	int hurt_radius; //基础伤害半径
	int speed; //移动速度
	int x_dir; //x-移动方向
	int y_dir; //y-移动方向

public:
	friend class Game1;
	friend class Weapon;
	friend class Shop;
	friend class Atkwing;
	friend class Bullet;

	Character();
	Character(QObject *parent);
	virtual void draw(QPainter* painter) const = 0;
	~Character();

	//实现攻击和被攻击的函数
	virtual void attacked(Enemy* enemy);
	virtual void attack(Enemy* enemy);

	//判断敌人是否在基础攻击范围内部
	bool contain(Enemy* ene);

	//经验和等级的提升
	void promote(int n);

	//得到基本属性的函数
	int getx();
	int gety();
	int getcur_hp();
	int getmax_hp();
	int getatk_v();
	int getspeed();
	int getxdir();
	int getydir();

	int enhance_atk_value = 0;
	int enhance_hr_value = 0;
	int enhance_speed_value = 0;
};
