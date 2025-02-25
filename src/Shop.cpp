#include "Shop.h"
#include <qpushbutton.h>
#include <qpainter.h>
#include "Game1.h"
#include "VampireSurvivors.h"
#include "Character.h"

Shop::Shop(Game1* parent)
	: ui(new Ui::ShopClass())
{
	ui->setupUi(this);
	game_parent = parent;
	
	this->setFixedSize(800, 400);

	QFont font;
	font.setFamily("Microsoft YaHei");
	font.setBold(true);
	font.setPointSizeF(10);

	QPushButton* finish = new QPushButton("Finish",this);
	finish->setGeometry(750, 350, 50, 50);
	finish->setFont(font);
	font.setPointSize(14);
	connect(finish, &QPushButton::clicked, this, [=]() {
		this->hide();
		});

	QPushButton* player_atk = new QPushButton("play_atk 30coins", this);
	player_atk->setGeometry(50, 50, 200, 100);
	player_atk->setFont(font);
	player_atk->setFlat(true);
	connect(player_atk, &QPushButton::clicked, this, [=]()
		{
			coin_consume(30); 
			game_parent->player_atk_enhance += 10;
			update();
		});
	QPushButton* player_hr = new QPushButton("hurt_radius 30coins", this);
	player_hr->setGeometry(50, 150, 200, 100);
	player_hr->setFont(font);
	player_hr->setFlat(true);
	connect(player_hr, &QPushButton::clicked, this, [=]()
		{
			coin_consume(30);
			game_parent->player_hr_enhance += 5;
			update();
		});
	QPushButton* player_speed = new QPushButton("speed 30coins", this);
	player_speed->setGeometry(50, 250, 200, 100);
	player_speed->setFont(font);
	player_speed->setFlat(true);
	connect(player_speed, &QPushButton::clicked, this, [=]()
		{
			coin_consume(30);
			game_parent->player_speed_enhance += 3;
			update();
		});

	QPushButton* weapon_atk = new QPushButton("weapon_atk 20coins", this);
	weapon_atk->setGeometry(300, 50, 200, 100);
	weapon_atk->setFont(font);
	weapon_atk->setFlat(true);
	connect(weapon_atk, &QPushButton::clicked, this, [=]()
		{
			coin_consume(20);
			game_parent->weapon_atk_enhance += 10;
			update();
		});
	QPushButton* weapon_hr = new QPushButton("hurt_radius 20coins", this);
	weapon_hr->setGeometry(300, 150, 200, 100);
	weapon_hr->setFont(font);
	weapon_hr->setFlat(true);
	connect(weapon_hr, &QPushButton::clicked, this, [=]()
		{
			coin_consume(20);
			game_parent->weapon_hr_enhance += 5;
			update();
		});
	QPushButton* weapon_speed = new QPushButton("speed 20coins", this);
	weapon_speed->setGeometry(300, 250, 200, 100);
	weapon_speed->setFont(font);
	weapon_speed->setFlat(true);
	connect(weapon_speed, &QPushButton::clicked, this, [=]()
		{
			coin_consume(20);
			game_parent->weapon_speed_enhance += 5;
			update();
		});
	
	QPushButton* coin_frequency = new QPushButton("coin_frequency 50coins", this);
	coin_frequency->setGeometry(550, 50, 200, 100);
	coin_frequency->setFont(font);
	coin_frequency->setFlat(true);
	connect(coin_frequency, &QPushButton::clicked, this, [=]()
		{
			coin_consume(50);
			game_parent->item_frequency -= 50;
			update();
		});
	QPushButton* realive = new QPushButton("realive times 500coins", this);
	realive->setGeometry(550, 150, 200, 100);
	realive->setFont(font);
	realive->setFlat(true);
	connect(realive, &QPushButton::clicked, this, [=] {
		coin_consume(500);
		game_parent->realive_times += 1;
		game_parent->temp_realive_times += 1;
		});
	update();
}


Shop::~Shop()
{
	delete ui;
}

void Shop::coin_consume(int n) {
	if (game_parent->total_coin_num >= n) {
		game_parent->total_coin_num -= n;
	}
}

void Shop::paintEvent(QPaintEvent*)
{
	QPainter* painter = new QPainter(this);
	painter->save();

	painter->drawPixmap(0, 0, 800, 400, QString(":/image/shop.png"));
	painter->drawPixmap(50, 50, 200, 100, QString(":/image/shop_1.png"));
	painter->drawPixmap(50, 150, 200, 100, QString(":/image/shop_1.png"));
	painter->drawPixmap(50, 250, 200, 100, QString(":/image/shop_1.png"));
	painter->drawPixmap(300, 50, 200, 100, QString(":/image/shop_2.png"));
	painter->drawPixmap(300, 150, 200, 100, QString(":/image/shop_2.png"));
	painter->drawPixmap(300, 250, 200, 100, QString(":/image/shop_2.png"));
	painter->drawPixmap(550, 50, 200, 100, QString(":/image/shop_3.png"));
	painter->drawPixmap(550, 150, 200, 100, QString(":/image/shop_3.png"));

	QFont font;
	font.setFamily("Microsoft YaHei");
	font.setBold(true);
	font.setPointSizeF(20);
	painter->save();
	painter->setPen(Qt::yellow);
	painter->setFont(font);
	painter->drawText(QRect(550, 300, 200, 100), QString("coin nums: %1").arg(game_parent->total_coin_num));
	painter->restore();
}
