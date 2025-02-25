#include "Enhancement.h"
#include <qpushbutton.h>
#include "Game1.h"

Enhancement::Enhancement(Game1*parent)
	:ui(new Ui::EnhancementClass())
{
	ui->setupUi(this);
	game = parent;

	this->setFixedSize(400, 700);

	QFont font;
	font.setPointSize(20);
	font.setFamily("Cooper Black");

	QPushButton* button1 = new QPushButton("Atk Enhance", this);
	button1->setGeometry(0, 100, 400, 200);
	button1->setFont(font);
	button1->setFlat(true);
	QPushButton* button2 = new QPushButton("Weapon Enhance", this);
	button2->setGeometry(0, 300, 400, 200);
	button2->setFont(font);
	button2->setFlat(true);
	QPushButton* button3 = new QPushButton("Speed Enhance", this);
	button3->setGeometry(0, 500, 400, 200);
	button3->setFont(font);
	button3->setFlat(true);

	update();

	connect(button3, &QPushButton::clicked, this, [=]() {
		game->cur_state = 1;
		game->enhance_speed();
		this->hide();
		});
	connect(button2, &QPushButton::clicked, this, [=]() {
		game->cur_state = 1;
		game->enhance_weapon();
		this->hide();
		});
	connect(button1, &QPushButton::clicked, this, [=]() {
		game->cur_state = 1;
		game->enhance_player();
		this->hide();
		});

}

Enhancement::~Enhancement()
{
	delete ui;
}

void Enhancement::paintEvent(QPaintEvent*) {
	QPainter* painter = new QPainter(this);
	QFont font;
	font.setFamily("Cooper Black");
	font.setBold(true);
	font.setPointSizeF(40);
	painter->save();
	painter->setPen(Qt::red);
	painter->setFont(font);
	painter->drawPixmap(0, 0, 400, 100, QString(":/image/level_up.png"));
	painter->setPen(Qt::red);
	painter->drawText(QRect(80, 20, 400, 200), QString("Level Up!"));
	painter->drawPixmap(0, 100, 400, 200, QString(":/image/enhance_1.png"));
	painter->drawPixmap(0, 300, 400, 200, QString(":/image/enhance_1.png"));
	painter->drawPixmap(0, 500, 400, 200, QString(":/image/enhance_1.png"));
	painter->restore();
}
