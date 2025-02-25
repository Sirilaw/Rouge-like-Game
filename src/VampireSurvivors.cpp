#include "VampireSurvivors.h"
#include <qpushbutton.h>
#include <qimage.h>
#include <qpainter.h>
#include "Game1.h"

class Game1;

VampireSurvivors::VampireSurvivors(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VampireSurvivorsClass())
{
    //设置游戏界面大小
    ui->setupUi(this);
    this->setFixedSize(1200, 800);
    //设置一个开始游戏的按钮
    QPushButton* start = new QPushButton("START",this);
    start->setGeometry(500, 650, 200, 50);
    start->setParent(this);
    start->setFont(QFont("Cooper Black", 25));
    start->setFlat(true);
    connect(start, &QPushButton::clicked, [=]() {
        this->hide(); //注意，这里调用的是hide()函数而不是close，所以最后一层析构发生在Vampire Survivors中
        game = new Game1(this);
        game->show(); 
    });

    //设置一个退出游戏的按钮
    QPushButton* exit = new QPushButton("Exit", this);
    exit->setGeometry(1150, 750, 50, 50);
    exit->setParent(this);
    exit->setFont(QFont("Times New Roman", 18));
    exit->setFlat(true);
    connect(exit, &QPushButton::clicked, this, &VampireSurvivors::close);
}

VampireSurvivors::~VampireSurvivors()
{
    game->~Game1();
    delete ui;
}

void VampireSurvivors::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QFont font;
    font.setPointSizeF(40);
    font.setFamily("Goudy Stout");
    font.setBold(true);
    QRect info(300, 250, 600, 360);
    painter.setFont(font);
 
    QString bk(":/image/mainwindow.png");  //path是图片的路径

    QString intro(":/image/introduction.png");
    QString start(":/image/start_button.png");
    painter.drawPixmap(0, 0, 1200, 800, bk);
    painter.drawPixmap(300, 200, 600, 400, intro);
    painter.setPen(Qt::red);
    painter.drawText(QRect(320, 0, 560, 250), Qt::AlignHCenter | Qt::AlignVCenter, "LiGengxi");

    font.setPointSizeF(30);
    font.setFamily("Bradley Hand ITC");
    painter.setFont(font);
    painter.setPen(Qt::blue);
    painter.drawText(info, "This is a rougue like game.\nWhat you have to do is to survive as long \
time as you can.\nYou can use coins you gain in the game to enhance your player's skills.\nGood luck to you, guy!");

    painter.drawPixmap(500, 650, 200, 50, start);
}
