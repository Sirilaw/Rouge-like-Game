#pragma once

#include <QObject>

class Map;

class Grid  : public QObject
{
	Q_OBJECT

public:
	friend class Map;
	friend class Game1;

	Grid();
	Grid(int xn, int yn, int type);
	~Grid();

private:
	int xn, yn; //xn的范围是1-30, yn的范围是1-20(格子本身的坐标[按个数计算])
	int type; //地块类型(0为障碍物,1为草地,2为灌木丛,3为黄土地)

	int isCoin; //表示有无金币掉落
	int isExpr; //表示有无经验掉落
};

