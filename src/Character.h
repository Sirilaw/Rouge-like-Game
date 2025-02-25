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
	QString imagepath; //��¼��ɫͼƬ����·��

	Game1* window;

	int ex, ey; //λ������
	int cur_hp; //��ǰѪ��
	int max_hp; //���Ѫ��

	int cur_experience = 0; //��ǰ����ֵ
	int cur_level = 1; //��ǰ�ȼ�
	
	int weapon; //����
	int atk_value; //��������ֵ
	int hurt_radius; //�����˺��뾶
	int speed; //�ƶ��ٶ�
	int x_dir; //x-�ƶ�����
	int y_dir; //y-�ƶ�����

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

	//ʵ�ֹ����ͱ������ĺ���
	virtual void attacked(Enemy* enemy);
	virtual void attack(Enemy* enemy);

	//�жϵ����Ƿ��ڻ���������Χ�ڲ�
	bool contain(Enemy* ene);

	//����͵ȼ�������
	void promote(int n);

	//�õ��������Եĺ���
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
