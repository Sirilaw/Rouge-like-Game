#include <qpainter.h>
#include <qpushbutton.h>
#include <qtimer.h>
#include <qelapsedtimer.h>
#include <qmessagebox.h>
#include <qaction.h>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <qtimer.h>
#include "Game1.h"
#include "Antony.h"
#include "Skeleton.h"
#include "Sigma.h"
#include "Ghost.h"
#include "Atkwing.h"
#include "VampireSurvivors.h"
#include "Enhancement.h"
#include "Shop.h"
#include "Bullet.h"
using namespace std;
Game1::Game1(VampireSurvivors *parent)
	: ui(new Ui::Game1Class())
{
	/*QSoundEffect* music_effect = new QSoundEffect(this);
	music_effect->setSource(QUrl::fromLocalFile("D:\\Vampire Survivors\\music\\The Verdant Grove LOOP.wav"));
	music_effect->setVolume(30);
	music_effect->play();*/
	parent_vamp = parent;
	//----------------------------
	cur_state = 0; //��Ϸ״̬�ĳ�ʼ��
	//----------------------------
	player_produced = 0;
	killed_num = 0;
	//---------------------------------------
	//���ļ��а�ȫ����Ϣ����������Game1��ȫ�ֱ���
	ifstream global_information;
	global_information.open("D:\\Vampire Survivors\\document.txt");
	if (!global_information) exit(-1);
	string line;
	while (getline(global_information, line)) {
		stringstream ss(line);
		ss >> total_coin_num >> \
			player_atk_enhance >> player_hr_enhance >> player_speed_enhance >> \
			weapon_atk_enhance >> weapon_hr_enhance >> weapon_speed_enhance >> \
			item_frequency >> max_survival_time >> max_enemy_killed_num >> realive_times;
	}
	temp_realive_times = realive_times;
	//---------------------------------------
	//ΪGame1�������ô�С
	ui->setupUi(this);
	this->setFixedSize(1400, 800); //���ڽ����СΪ1200 * 800  ��30 * 20(������������) (ΪfixedSize)
	//��ͼ���������
	map = new Map();
	//timer�Ĵ����ͳ�ʼ��
	timer = new QTimer(this);
	timer->setInterval(50);
	timer->start();
	//���г�ʼ��Ϸ���ã���ʵ���ǽ�ɫ��ѡ��
	set();
	QPushButton* exit_game = new QPushButton("E", this);
	exit_game->setGeometry(1300, 600, 100, 100);
	exit_game->setFont(QFont("Cooper Black", 30));
	exit_game->setStyleSheet("QPushButton{border-image:url(:/image/exit.png);}");
	connect(exit_game, &QPushButton::clicked, [=] {this->close(); });
	QPushButton* halt_game = new QPushButton("H", this);
	halt_game->setGeometry(1300, 700, 100, 100);
	halt_game->setFont(QFont("Cooper Black", 30));
	halt_game->setStyleSheet("QPushButton{border-image:url(:/image/halt.png);}");
	connect(halt_game, &QPushButton::clicked, [=] {
		if (halt_flag == 0) {
			halt_flag = 1;
			timer->stop();
		}
		else {
			halt_flag = 0;
			timer->start();
		}
		});
	//д��connect����
	connect(timer, &QTimer::timeout, this, [=]()
		{
			if (cur_state) {
				halt_game->setGeometry(1200, 650, 100, 100);
				exit_game->setGeometry(1300, 650, 100, 100);
			}
			//����cur_state���жϵ�ǰҪ��ʲô����
			if (cur_state == 1) { //ֻ�е�������õ�ʱ��Ż�����
				run_time += 50;
				run();
			}
			else if (cur_state == 2) {
				timer->stop();
				enhance();
				timer->start();
			}
			else if (cur_state == 3) {
				timer->stop();
				if (temp_realive_times > 0) {
					temp_realive_times -= 1;
					QTimer* temp = new QTimer(this);
					temp->setInterval(2500);
					temp->start();
					player->cur_hp = player->max_hp;
					connect(temp, &QTimer::timeout, this, [=] {
						cur_state = 1;
						timer->start();
						delete temp;
						});
				}
				else {
					//��Ϸ����ʱ��Ҫ�ɵ����飨���ǲ�֪��Ϊʲôд�����������װ����ִ���߼��ͻ�������⣩
					if (run_time / 1000 > max_survival_time) {
						max_survival_time = run_time / 1000;
					}
					if (killed_num > max_enemy_killed_num) {
						max_enemy_killed_num = killed_num;
					}
					ofstream global_information;
					global_information.open("D:\\Vampire Survivors\\document.txt");
					if (!global_information) exit(-1);
					global_information << total_coin_num << " " << player_atk_enhance << " " << player_hr_enhance << " " << player_speed_enhance << " " << \
						weapon_atk_enhance << " " << weapon_hr_enhance << " " << weapon_speed_enhance << " " << \
						item_frequency << " " << max_survival_time << " " << max_enemy_killed_num << " " << realive_times;
				}
			}
		});
	//�Ȱ�enhancement���ں�shop���ڴ�����
	en = new Enhancement(this);
	shop = new Shop(this);
}
//Game1���ڵ���������
Game1::~Game1()
{
	//�����Ϸ��û��������������player��ɱ���Ľ�����ʽ������ֱ�Ӱ���Ϸ���ˣ��������ִ浵��ʽ.
	//�����ִ浵��ʽ�в������max_enemy_killed_num��max_survival_time.
	ofstream global_information;
	global_information.open("D:\\Vampire Survivors\\document.txt");
	if (!global_information) exit(-1);
	global_information << total_coin_num << \
		" " << player_atk_enhance << " " << player_hr_enhance << " " << player_speed_enhance << " " << \
		weapon_atk_enhance << " " << weapon_hr_enhance << " " << weapon_speed_enhance << " " << \
		item_frequency << " " << max_survival_time << " " << max_enemy_killed_num << " " << realive_times;
	delete ui;
}
//��Ϸѡ�����ﺯ��
void Game1::set()
{
	//����2��ѡ������İ�ť
	QFont font;
	font.setPointSize(20);
	font.setFamily("Castellar");
	font.setBold(true);
	QPushButton* button1 = new QPushButton("Antony", this);
	button1->setGeometry(400, 470, 200, 150);
	button1->setFont(font);
	button1->setFlat(true);
	QPushButton* button2 = new QPushButton("Sigma", this);
	button2->setGeometry(800, 470, 200, 150);
	button2->setFont(font);
	button2->setFlat(true);
	//����һ�������̵�İ�ť
	QPushButton* shopbutton = new QPushButton("SHOP", this);
	shopbutton->setGeometry(500, 650, 400, 100);
	shopbutton->setFlat(true);
	shopbutton->setFont(QFont("Cooper Black", 40));
	connect(shopbutton, &QPushButton::clicked, [=]() {shop->show(); });
	update();
	connect(button2, &QPushButton::clicked, this, [=]() {
		player_type = 1;
		player_produce();
		cur_state = 1;
		delete button1;
		delete button2;
		delete shopbutton;
	});
	connect(button1, &QPushButton::clicked, this, [=]() {
		player_type = 0;
		player_produce();
		cur_state = 1;
		delete button1;
		delete button2;
		delete shopbutton;
	});
}
//��Ϸ��������һ��
void Game1::run()
{
	drop_items();
	player_move();
	player_atk();
	weapon_produce();
	weapon_move();
	enemy_atk();
	enemy_produce();
	update();
}
//����ǿ������
void Game1::enhance()
{
	en->show();
}
//items�ĵ��亯��
void Game1::drop_items()
{
	srand(time(0));
	int type = rand() % 2;
	int xn, yn;
	if (run_time % item_frequency == 0) { //1800��Ҫ��Ϊitem_frequency
		xn = rand() % 30;
		yn = rand() % 20;
		if (type == 0 && (map->gmap)[xn][yn]->type != 0) {
			(map->gmap)[xn][yn]->isCoin = 1;
		}
		else if (type == 1 && (map->gmap)[xn][yn]->type != 0) {
			(map->gmap)[xn][yn]->isExpr = 1;
		}
	}
}
//player�Ĳ�������
void Game1::player_produce()
{
	switch (player_type) {
	case 0: {
		player = new Antony(QPoint(400, 400), this);
		break;
	}
	case 1: {
		player = new Sigma(QPoint(400, 400), this);
		break;
	}
	}
	player_produced = 1;
}
//enemy��ˢ�º���
void Game1::enemy_produce()
{
	int enemy_type = rand() % 2 + 1; //�ó������ĵ��˵�����
	if (run_time % enemy_produce_frequency == 0) { //
		int opt = rand() % 4 + 1;
		int x = 0, y = 0;
		switch (opt) {
		case 1: { //���Ϸ���Եˢ�½���
			x = (rand() % 30) * 40;
			y = 25;
			break;
		}
		case 2: { //���·���Եˢ�½���
			x = (rand() % 30) * 40;
			y = 775;
			break;
		}
		case 3: { //������Եˢ�½���
			x = 25;
			y = (rand() % 20) * 40;
			break;
		}
		case 4: { //���Ҳ��Եˢ�½���
			x = 1175;
			y = (rand() % 20) * 40;
			break;
		}
		}
		switch (enemy_type) {
		case 1: {
			Skeleton* ske = new Skeleton(QPoint(x, y), this);
			enemy_vec.push_back(ske);
			break;
		}
		case 2: {
			Ghost* ghost = new Ghost(QPoint(x, y), this);
			enemy_vec.push_back(ghost);
			break;
		}
		}
	}
}
//enemy����player�ĺ���
void Game1::enemy_atk()
{
	for (auto it = enemy_vec.begin(); it != enemy_vec.end(); it++) {
		(*it)->attack(player);
	}
}
//player����enenmy�ĺ���
void Game1::player_atk()
{
	for (auto it = enemy_vec.begin(); it != enemy_vec.end(); it++) {
		if (player->contain(*it)) {
			player->attack(*it);
		}
	}
}
//player���ƶ�����
void Game1::player_move()
{
	switch (key_press_sign) {
	case 1: { //W��
		player->y_dir = -1;
		player->x_dir = 0;
		player->ey -= player->speed;
		int yn = player->ey / 40;
		if ((map->gmap)[player->ex / 40][yn]->type == 0) {
			player->ey = 40 * (yn + 1) + 20;
		}
		if (player->ey <= 20) {
			player->ey = 20;
		}
		if ((map->gmap)[player->ex / 40][yn]->isCoin == 1) {
			(map->gmap)[player->ex / 40][yn]->isCoin = 0;
			one_coin_num++;
			total_coin_num++;
		}
		if ((map->gmap)[player->ex / 40][yn]->isExpr == 1) {
			(map->gmap)[player->ex / 40][yn]->isExpr = 0;
			player->cur_experience += 10;
		}
		break;
	}
	case 2: { //A��
		player->x_dir = -1;
		player->y_dir = 0;
		player->ex -= player->speed;
		int xn = player->ex / 40;
		if ((map->gmap)[xn][player->ey / 40]->type == 0) {
			player->ex = 40 * (xn + 1) + 20;
		}
		if (player->ex <= 20) {
			player->ex = 20;
		}
		if ((map->gmap)[xn][player->ey / 40]->isCoin == 1) {
			(map->gmap)[xn][player->ey / 40]->isCoin = 0;
			one_coin_num++;
			total_coin_num++;
		}
		if ((map->gmap)[xn][player->ey / 40]->isExpr == 1) {
			(map->gmap)[xn][player->ey / 40]->isExpr = 0;
			player->cur_experience += 10;
		}
		break;
	}
	case 3: { //S��
		player->y_dir = 1;
		player->x_dir = 0;
		player->ey += player->speed;
		int yn = player->ey / 40;
		if ((map->gmap)[player->ex / 40][yn]->type == 0) {
			player->ey = 40 * (yn)-20;
		}
		if (player->ey >= 780) {
			player->ey = 780;
		}
		if ((map->gmap)[player->ex / 40][yn]->isCoin == 1) {
			(map->gmap)[player->ex / 40][yn]->isCoin = 0;
			one_coin_num++;
			total_coin_num++;
		}
		if ((map->gmap)[player->ex / 40][yn]->isExpr == 1) {
			(map->gmap)[player->ex / 40][yn]->isExpr = 0;
			player->cur_experience += 10;
		}
		break;
	}
	case 4: { //D��
		player->x_dir = 1;
		player->y_dir = 0;
		player->ex += player->speed;
		int xn = player->ex / 40;
		if ((map->gmap)[xn][player->ey / 40]->type == 0) {
			player->ex = 40 * (xn)-20;
		}
		if (player->ex >= 1180) {
			player->ex = 1180;
		}
		if ((map->gmap)[xn][player->ey / 40]->isCoin == 1) {
			(map->gmap)[xn][player->ey / 40]->isCoin = 0;
			one_coin_num++;
			total_coin_num++;
		}
		if ((map->gmap)[xn][player->ey / 40]->isExpr == 1) {
			(map->gmap)[xn][player->ey / 40]->isExpr = 0;
			player->cur_experience += 10;
		}
		break;
	}
	default: {
		player->x_dir = 0;
		player->y_dir = -1;
		return;
	}
	}
}
//weapon�Ĳ�������
void Game1::weapon_produce()
{
	if (run_time % 600 == 0) {
		switch (player_type) {
		case 0: {
			Bullet* bullet = new Bullet(player);
			bullet->atk_value += weapon_enhance_value;
			weapon_vec.push_back(bullet);
			break;
		}
		case 1: {
			Atkwing* wing = new Atkwing(player);
			wing->atk_value += weapon_enhance_value;
			weapon_vec.push_back(wing);
			break;
		}
		}
	}
}
//weapon���ƶ�����(����Ҳд��������)
void Game1::weapon_move()
{
	for (auto it = weapon_vec.begin(); it != weapon_vec.end();) {
		(*it)->move();
		int tx = (*it)->getx(), ty = (*it)->gety();
		(*it)->hittarget();
		if (tx <= 0 || tx >= 1200 || ty <= 0 || ty >= 800) {
			it = weapon_vec.erase(it);
		}
		else {
			it++;
		}
	}
}
//player enhancement
void Game1::enhance_player() //player�Ĺ���ֵ����
{
	player->atk_value += 10;
}
//weapon enhancement
void Game1::enhance_weapon() //�²�����weapon�Ĺ���ֵ����
{
	weapon_enhance_value += 10;
}
//speed enhancement
void Game1::enhance_speed() //player��speed����
{
	player->speed += 2;
}
//����keyPressEvent����
void Game1::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_W) {
		key_press_sign = 1;
	}
	else if (event->key() == Qt::Key_A) {
		key_press_sign = 2;
	}
	else if (event->key() == Qt::Key_S) {
		key_press_sign = 3;
	}
	else if (event->key() == Qt::Key_D) {
		key_press_sign = 4;
	}
	else if (event->key() == Qt::Key_Escape) {
		key_press_sign = 5;
	}
}
//����keyReleaseEvent����
void Game1::keyReleaseEvent(QKeyEvent* event)
{
	key_press_sign = 0;
}
//����paintEvent����
void Game1::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	painter.save();

	QString path_1 = ":/image/Antonio.jpg";
	QString path_2 = ":/image/Sigma.jpg";

	if (cur_state == 0) { //���ý���,��������ɫ��ͼƬ��һ�¾�����
		QFont font;
		font.setPointSizeF(30);
		font.setFamily("Goudy Stout");
		font.setBold(true);
		QRect info(300, 250, 600, 360);
		painter.setFont(font);
		painter.setPen(Qt::red);

		painter.drawPixmap(0, 0, 1400, 800, QString(":/image/setbk.png"));
		painter.drawPixmap(350, 170, 300, 300, QString(":/image/shelf.png"));
		painter.drawPixmap(750, 170, 300, 300, QString(":/image/shelf.png"));
		painter.drawPixmap(400, 500, 200, 100, QString(":/image/start_button.png"));
		painter.drawPixmap(800, 500, 200, 100, QString(":/image/start_button.png"));
		painter.drawPixmap(500, 650, 400, 100, QString(":/image/shopbutton.png"));

		painter.drawPixmap(400, 270, 200, 150, path_1);
		painter.drawPixmap(800, 270, 200, 150, path_2);

		painter.drawText(QRect(300, 30, 800, 100), Qt::AlignHCenter | Qt::AlignVCenter, "Choose Player");
	}
	else {
		//���Ƶ�ͼ
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 20; j++) {
				painter.drawPixmap(40 * i, 40 * j, 40, 40, map->typestr[(map->gmap)[i][j]->type]);
				if ((map->gmap)[i][j]->isCoin == 1) {
					painter.drawPixmap(40 * i, 40 * j, 40, 40, QString(":/image/Coin2.png"));
				}
				if ((map->gmap)[i][j]->isExpr == 1) {
					painter.drawPixmap(40 * i, 40 * j, 40, 40, QString(":/image/Battery.png"));
				}
			}
		}
		//�������
		player->draw(&painter); //player��ex��ey�ı仯��keyPressEvent�и���
		//���Ƶ���(����)
		for (auto it = enemy_vec.begin(); it != enemy_vec.end();) {
			if ((*it)->die == 1) {
				it = enemy_vec.erase(it);
			}
			else {
				(*it)->draw(&painter);
				it++;
			}
		}
		//��������
		for (auto it = weapon_vec.begin(); it != weapon_vec.end(); it++) {
			(*it)->draw(&painter);
		}
		painter.drawPixmap(1200, 0, 200, 800, QString(":/image/right_info.png"));
		painter.drawPixmap(1200, 0, 200, 50, QString(":/image/top_info.png"));
		painter.drawPixmap(1200, 750, 200, 50, QString(":/image/bottom_info.png"));
		//����player��ǰ����˶೤ʱ��
		drawTime(&painter);
		//���Ƶ�ǰɱ���˶��ٹ���
		drawDeadnum(&painter);
		draw_expr_level(&painter);
		drawCoin(&painter);
		drawRealive(&painter);
		//��ʱ��Ϸ״̬Ϊ��Ϸ��������Ҫ������Ϸ������ҳ��
		if (cur_state == 3) {
			if (temp_realive_times <= 0) {
				painter.drawPixmap(300, 100, 800, 600, QString(":/image/gameover_window.png"));
				QFont font;
				font.setFamily("Cooper Black");
				font.setBold(true);
				font.setPointSizeF(40);
				painter.setFont(font);
				painter.drawText(QRect(300, 100, 800, 100), Qt::AlignHCenter | Qt::AlignVCenter, QString("Game Over!"));
				font.setBold(false);
				font.setPointSizeF(30);
				painter.setFont(font);
				painter.setPen(Qt::green);
				if (run_time / 1000 > max_survival_time) {
					painter.drawText(QRect(300, 200, 800, 80), Qt::AlignHCenter | Qt::AlignVCenter, QString("Your survival time is %1s").arg(run_time / 1000));
					painter.drawText(QRect(300, 280, 800, 80), Qt::AlignHCenter | Qt::AlignVCenter, QString("Breaks your record %1s").arg(max_survival_time));
				}
				else {
					painter.drawText(QRect(300, 200, 800, 80), Qt::AlignHCenter | Qt::AlignVCenter, QString("Your survival time is %1s").arg(run_time / 1000));
					painter.drawText(QRect(300, 280, 800, 80), Qt::AlignHCenter | Qt::AlignVCenter, QString("%1s more to break your record").arg(max_survival_time - run_time / 1000));
				}
				if (killed_num > max_enemy_killed_num) {
					painter.drawText(QRect(300, 360, 800, 80), Qt::AlignHCenter | Qt::AlignVCenter, QString("Enemy killed is %1").arg(killed_num));
					painter.drawText(QRect(300, 440, 800, 80), Qt::AlignHCenter | Qt::AlignVCenter, QString("Breaks your record %1").arg(max_enemy_killed_num));
				}
				else {
					painter.drawText(QRect(300, 360, 800, 80), Qt::AlignHCenter | Qt::AlignVCenter, QString("Enemy killed is %1").arg(killed_num));
					painter.drawText(QRect(300, 440, 800, 80), Qt::AlignHCenter | Qt::AlignVCenter, QString("%1 more to break your record").arg(max_enemy_killed_num - killed_num));
				}
			}
			else {
				painter.drawPixmap(300, 100, 800, 600, QString(":/image/gameover_window.png"));
				QFont font;
				font.setFamily("Cooper Black");
				font.setBold(true);
				font.setPointSizeF(40);
				painter.setFont(font);
				painter.drawText(QRect(300, 350, 800, 100), Qt::AlignHCenter | Qt::AlignVCenter, QString("You will be alive again!"));
			}
		}
	}
}
//����Ϸ�����˶೤ʱ��
void Game1::drawTime(QPainter* painter)
{
	QFont font;
	font.setFamily("Microsoft YaHei");
	font.setBold(true);
	font.setPointSizeF(20);
	painter->save();
	painter->setPen(Qt::red);
	painter->setFont(font);
	painter->drawText(QRect(1200, 135, 200, 100), QString("Survival Time: %1secs").arg(run_time / 1000));
	painter->restore();
}
//������ɱ�����ٵ���
void Game1::drawDeadnum(QPainter* painter)
{
	QFont font;
	font.setFamily("Microsoft YaHei");
	font.setBold(true);
	font.setPointSizeF(20);
	painter->save();
	painter->setPen(Qt::red);
	painter->setFont(font);
	painter->drawText(QRect(1200, 55, 200, 100), QString("Enemy Killed: %1").arg(killed_num));
	painter->restore();
}
//������ֵ�͵ȼ�
void Game1::draw_expr_level(QPainter* painter)
{
	QFont font;
	font.setFamily("Cooper Black");
	font.setBold(true);
	font.setPointSizeF(20);
	painter->save();
	painter->setPen(Qt::blue);
	painter->setFont(font);
	painter->drawPixmap(1200, 215, 200, 50, QString(":/image/expr_00.png"));
	painter->drawPixmap(1210, 225, 25, 25, QString(":/image/expr_02.png"));
	int expr_num = player->cur_experience / 10;
	for (int i = 0; i < expr_num; i++) {
		painter->drawPixmap(1250 + 15 * i, 225, 15, 25, QString(":/image/expr_01.png"));
	}
	painter->drawText(QRect(1250, 270, 200, 100), QString("Level: %1").arg(player->cur_level));
	painter->restore();
}
//�����ڽ����
void Game1::drawCoin(QPainter* painter) {
	QFont font;
	font.setFamily("Microsoft YaHei");
	font.setBold(true);
	font.setPointSizeF(20);
	painter->save();
	painter->setPen(Qt::blue);
	painter->setFont(font);
	painter->drawText(QRect(1200, 325, 200, 100), QString("Coins: %1").arg(one_coin_num));
	painter->restore();
}
void Game1::drawRealive(QPainter* painter) {
	QFont font;
	font.setFamily("Microsoft YaHei");
	font.setBold(true);
	font.setPointSizeF(20);
	painter->save();
	painter->setPen(Qt::blue);
	painter->setFont(font);
	painter->drawText(QRect(1200, 385, 200, 100), QString("Your relive chance: %1").arg(temp_realive_times));
	painter->restore();
}