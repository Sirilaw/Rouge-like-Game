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
	int xn, yn; //xn�ķ�Χ��1-30, yn�ķ�Χ��1-20(���ӱ��������[����������])
	int type; //�ؿ�����(0Ϊ�ϰ���,1Ϊ�ݵ�,2Ϊ��ľ��,3Ϊ������)

	int isCoin; //��ʾ���޽�ҵ���
	int isExpr; //��ʾ���޾������
};

