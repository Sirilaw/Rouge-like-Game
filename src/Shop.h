#pragma once

#include <QWidget>
#include "ui_Shop.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ShopClass; };
QT_END_NAMESPACE

class Game1;
class VampireSurvivors;

class Shop : public QWidget
{
	Q_OBJECT

public:
	Shop(Game1*parent);
	~Shop();
	void coin_consume(int n);
	void paintEvent(QPaintEvent*);

private:
	Ui::ShopClass *ui;
	Game1* game_parent;
};
