#pragma once

#include <QObject>
#include "Grid.h"

class Grid;

class Map  : public QObject
{
	Q_OBJECT

public:
	friend class Grid;
	friend class Game1;

	Map();
	~Map();

private:
	int barrier_num = 20;
	Grid* gmap[30][20];
	QString typestr[4] = { ":/image/obstacle.png", ":/image/ground_1.png",":/image/ground_2.png",":/image/ground_4.png" };
};

