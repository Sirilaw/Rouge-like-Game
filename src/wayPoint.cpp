#include "wayPoint.h"

wayPoint::wayPoint(QPoint pos) :m_pos(pos), m_nextWayPoint(nullptr)
{

}

void wayPoint::setNextWayPoint(wayPoint* nextWayPoint) {
	this->m_nextWayPoint = nextWayPoint;
}

wayPoint* wayPoint::getNextWayPoint() {
	return m_nextWayPoint;
}

const QPoint wayPoint::getPos() {
	return this->m_pos;
}

void wayPoint::draw(QPainter* painter) const {
    painter->save();//����ԭʼ�Ļ滭����
    painter->setPen(Qt::green);//���û��ʵ���ɫ
    painter->drawEllipse(m_pos, 4, 4);//��һ���뾶Ϊ4��Բ
    //ע�⣬ͼƬ�Ĵ�С��λ������
    painter->drawEllipse(m_pos, 1, 1);//�뾶Ϊ1��Բ
    if (m_nextWayPoint)//���������һ�����㣬�Ͱ�������������������
    {
        painter->drawLine(m_pos, m_nextWayPoint->getPos());//painter�ڵĻ�ֱ�ߵķ���
    }
    painter->restore();//��ԭԭ���Ļ�������
}


wayPoint::~wayPoint()
{}
