#pragma once
#include <QWidget>
#include <QPaintEvent>
#include "ui_Game1.h"
#include <qpushbutton.h>
#include "Character.h"
#include <QTime>
#include <qelapsedtimer.h>
#include "Map.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Game1Class; };
QT_END_NAMESPACE

class Weapon;
class Settings;
class VampireSurvivors;
class Enhancement;
class Shop;
class Antony;
class Sigma;
class Atkwing;
class Bullet;

class Game1 : public QWidget
{
	Q_OBJECT

public:
	friend class Enemy;
	friend class Character;
	friend class Weapon;
	friend class Map;
	friend class Settings;
	friend class Enhancement;
	friend class Shop;
	friend class Antony;
	friend class Sigma;
	friend class Atkwing;
	friend class Bullet;

	QPushButton* back;
	explicit Game1(VampireSurvivors *parent = nullptr);
	~Game1();

	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);

signals:
	void btnClicked();

private:
	VampireSurvivors* parent_vamp;
	Enhancement* en;
	Shop* shop;
	int key_press_sign;
	int finished_set;
	int cur_state; //0 选角色; 1 正常进行游戏; 2 局内强化; 3 游戏结束
	//局内参数
	int player_type;
	int killed_num; //杀死的敌人数量
	int weapon_enhance_value = 0;
	int one_coin_num = 0;
	int run_time = 0;
	int halt_flag = 0;

	//全局参数
	int total_coin_num = 0; //金币数
	int exerience_needed = 100; //升级所需经验值
	int max_survival_time = 0;
	int max_enemy_killed_num = 0;

	int player_atk_enhance = 0;
	int player_hr_enhance = 0;
	int player_speed_enhance = 0;
	int weapon_atk_enhance = 0;
	int weapon_hr_enhance = 0;
	int weapon_speed_enhance = 0;

	int enemy_produce_frequency = 1800;
	int weapon_produce_frequency = 1800;
	int item_frequency = 1800; //应该也是全局变量(?)
	int realive_times = 0; //可以复活的次数
	int temp_realive_times = 0;

	Ui::Game1Class *ui;

	QTimer* timer;
	Map* map;
	Character* player;
	int player_produced;
	QVector <Weapon*> weapon_vec;
	QVector <Enemy*> enemy_vec;

	void set();
	void run();
	void enhance();
	void drop_items();
	void player_produce();
	void enemy_produce();
	void enemy_atk();
	void player_atk();
	void player_move();
	void weapon_produce();
	void weapon_move();

	void enhance_player();
	void enhance_weapon();
	void enhance_speed();

	void drawTime(QPainter*);
	void drawDeadnum(QPainter*);
	void draw_expr_level(QPainter* painter);
	void drawCoin(QPainter* painter);
	void drawRealive(QPainter* painter);

protected:
	void paintEvent(QPaintEvent*);
};