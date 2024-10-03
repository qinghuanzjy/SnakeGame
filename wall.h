#ifndef WALL_H
#define WALL_H
#include<QPointF>
class Wall
{
private:
    QPointF pos;
public:
    Wall();
    Wall(QPointF p);
    QPointF getPoint();
    void setPoint(QPointF p);
};

#endif // WALL_H
