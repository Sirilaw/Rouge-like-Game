#pragma once
#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QPoint>
#include <QPainter>

class wayPoint 
{
public:
	wayPoint(QPoint pos);
	void setNextWayPoint(wayPoint* nextWayPoint);
	wayPoint* getNextWayPoint();
	const QPoint getPos();
	void draw(QPainter* painter) const;
	~wayPoint();
private:
	QPoint m_pos;
	wayPoint* m_nextWayPoint;
};

#endif // !WAYPOINT_H
