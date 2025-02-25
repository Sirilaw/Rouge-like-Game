#pragma once

#include <QWidget>
#include "ui_Enhancement.h"

class Game1;


QT_BEGIN_NAMESPACE
namespace Ui { class EnhancementClass; };
QT_END_NAMESPACE

class Enhancement : public QWidget
{
	Q_OBJECT

public:
	Enhancement(Game1*parent = nullptr);
	~Enhancement();

	void paintEvent(QPaintEvent* painter);

private:
	Game1* game;
	Ui::EnhancementClass *ui;
};
